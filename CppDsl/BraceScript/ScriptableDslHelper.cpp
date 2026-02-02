#include "ScriptableDslHelper.h"
#include "DslParser.h"
#include "SlkConstants.h"

ScriptableDslHelper* ScriptableDslHelper::s_pForBraceScript = nullptr;

ScriptableDslHelper& ScriptableDslHelper::ForBraceScript()
{
    if (nullptr == s_pForBraceScript) {
        s_pForBraceScript = new ScriptableDslHelper();

    }
    return *s_pForBraceScript;
}

ScriptableDslHelper::ScriptableDslHelper() :
    m_NameTags{
        { "if", PAIR_TAG_IF },
        { "elseif", PAIR_TAG_ELSEIF },
        { "elif", PAIR_TAG_ELIF },
        { "while", PAIR_TAG_WHILE },
        { "foreach", PAIR_TAG_FOREACH },
        { "loop", PAIR_TAG_LOOP },
        { "looplist", PAIR_TAG_LOOPLIST }
},
m_FirstLastKeyOfCompoundStatements{
      { "if", "else" },
      { "while", "while" },
      { "foreach", "foreach" },
      { "loop", "loop" },
      { "loopi", "loopi" },
      { "loopd", "loopd" },
      { "looplist", "looplist" },
      { "struct", "struct" }
},
m_SuccessorsOfCompoundStatements{
    {
        "if", { "elseif", "elif", "else" }
    },
    {
        "elseif", { "elseif", "elif", "else" }
    },
    {
        "elif", { "elseif", "elif", "else" }
    },
    {
        "else", {}
    },
    {
        "while", {}
    },
    {
        "foreach", {}
    },
    {
        "loop", {}
    },
    {
        "looplist", {}
    },
    {
        "struct", {}
    },
    {
        "script", { "params", "args" }
    },
    {
        "story", { "params", "args" }
    }
},
m_CompoundStatements{
        "if", "while", "foreach", "loop", "looplist", "struct", "script", "story"
}
{
}

void ScriptableDslHelper::SetCallbacks(DslParser::DslFile& dataFile)
{
    dataFile.NameTagsRef() = m_NameTags;

    dataFile.OnGetToken.attach(this, &ScriptableDslHelper::OnGetToken);
    dataFile.OnBeforeAddFunction.attach(this, &ScriptableDslHelper::OnBeforeAddFunction);
    dataFile.OnAddFunction.attach([](auto& api, auto* sd, auto* func) {
        (void)api, (void)sd, (void)func;
        //Do not change the program structure here. At this point, the "function" is still an empty function, and the real function information has not been filled in.
        //The difference between this and "onBeforeAddFunction" is that the "function" is constructed and added to the function table of the current statement.
        return false;
        });
    dataFile.OnBeforeEndStatement.attach([](auto& api, auto* sd) {
        (void)api, (void)sd;
        //The program structure can be modified in BeforeEndStatement, and it must comply with the syntax and semantic process of DSL.
        return false;
        });
    dataFile.OnEndStatement.attach([](auto& api, auto*& sd) {
        (void)api, (void)sd;
        //Generally, the program structure should not be modified in EndStatement, but the current statement can be modified or replaced as a whole.
        //After the callback, the statement will be simplified and added to the upper level syntax structure.
        return false;
        });
    dataFile.OnBeforeBuildOperator.attach([](auto& api, auto category, auto* ch, auto* sd) {
        (void)api, (void)category, (void)ch, (void)sd;
        //The statement can be split here.
        return false;
        });
    dataFile.OnBuildOperator.attach([](auto& api, auto category, auto* ch, auto*& sd) {
        (void)api, (void)category, (void)ch, (void)sd;
        //The statement can be replaced here, but do not modify other syntax structures.
        return false;
        });
    dataFile.OnSetFunctionId.attach(this, &ScriptableDslHelper::OnSetFunctionId);
    dataFile.OnBeforeBuildHighOrder.attach([](auto& api, auto* sd, auto* fd) {
        (void)api, (void)sd, (void)fd;
        //The statement can be split here.
        return false;
        });
    dataFile.OnBuildHighOrder.attach([](auto& api, auto* sd, auto* fd) {
        (void)api, (void)sd, (void)fd;
        //The statement can be split here.
        return false;
        });
}

bool ScriptableDslHelper::OnGetToken([[maybe_unused]] const DslParser::DslActionApi& actionApi, const DslParser::DslTokenApi& tokenApi, char*& tok, [[maybe_unused]] short& val, int& line)
{
    if (IDENTIFIER_ == val && 0 == strcmp(tok, "return")) {
        char* oldCurTok = tokenApi.getCurToken();
        char* oldLastTok = tokenApi.getLastToken();
        int index;
        char nc = tokenApi.peekNextValidChar(0, index);
        if (nc == ';')
            return false;
        tokenApi.setCurToken(const_cast<char*>("`"));
        tokenApi.setLastToken(oldCurTok);
        tokenApi.enqueueToken(tokenApi.getCurToken(), tokenApi.getOperatorTokenValue(), line);
        tokenApi.setCurToken(oldCurTok);
        tokenApi.setLastToken(oldLastTok);
        return true;
    }
    else if (RPAREN_ == val && 0 == strcmp(tok, ")")) {
        uint32_t tag;
        if (actionApi.peekPairTypeStack(tag) == IDslSyntaxCommon::PAIR_TYPE_PARENTHESES) {
            if (tag > 0) {
                char* oldCurTok = tokenApi.getCurToken();
                char* oldLastTok = tokenApi.getLastToken();
                int index;
                char nc = tokenApi.peekNextValidChar(0, index);
                if (nc == '{' || nc == ',' || nc == ';')
                    return false;
                //insert backtick char
                tokenApi.setCurToken(const_cast<char*>("`"));
                tokenApi.setLastToken(oldCurTok);
                tokenApi.enqueueToken(tokenApi.getCurToken(), tokenApi.getOperatorTokenValue(), line);
                tokenApi.setCurToken(oldCurTok);
                tokenApi.setLastToken(oldLastTok);
                return true;
            }
        }
    }
    return false;
}

bool ScriptableDslHelper::OnBeforeAddFunction(const DslParser::DslActionApi& api, DslParser::StatementData* sd)const
{
    //You can end the current statement here and start a new empty statement.
    (void)api, (void)sd;
    const char* fid = sd->GetId();
    auto* func = sd->GetLast()->AsFunction();
    if (nullptr != func) {
        const char* lid = func->GetId();
        if (func->HaveStatement()) {
            bool match = false;
            if (fid && fid[0]) {
                auto&& it = m_FirstLastKeyOfCompoundStatements.find(fid);
                if (it != m_FirstLastKeyOfCompoundStatements.end() && it->second == lid) {
                    match = true;
                }
            }
            if (nullptr == fid || fid[0] == 0 || match) {
                //End the current statement and start a new empty statement.
                api.endStatement();
                api.beginStatement();
                return true;
            }
        }
    }
    return false;
}

bool ScriptableDslHelper::OnSetFunctionId(const DslParser::DslActionApi& api, const char* name, DslParser::StatementData* sd, DslParser::FunctionData* fd)const
{
    //The statement can be split here.
    (void)api, (void)name, (void)sd, (void)fd;
    auto* sid = sd->GetId();
    auto* func = sd->GetLast()->AsFunction();
    if (nullptr != func && sd->GetFunctionNum() > 1) {
        bool match = false;
        if (sid && sid[0]) {
            auto it = m_SuccessorsOfCompoundStatements.find(sid);
            if (it != m_SuccessorsOfCompoundStatements.end() && it->second.find(name) == it->second.end()) {
                match = true;
            }
        }
        if (match) {
            sd->RemoveLastFunction();
            api.endStatement();
            api.beginStatement();
            auto* stm = api.getCurStatement();
            stm->AddFunction(func);
            return true;
        }
        else if (m_CompoundStatements.find(name) != m_CompoundStatements.end()) {
            sd->RemoveLastFunction();
            api.endStatement();
            api.beginStatement();
            auto* stm = api.getCurStatement();
            stm->AddFunction(func);
            return true;
        }
    }
    return false;
}
