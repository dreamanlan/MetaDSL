// Dsl.cpp : 定义控制台应用程序的入口点。
//
#include "BaseType.h"
#include "Dsl.h"
#include "BraceScript.h"
#include "SimpleCoroutine.h"
#include "ShareStackCoroutine.h"
#include "BraceCoroutine.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>

void InitScript(DslParser::IDslStringAndObjectBuffer* pBuffer, const std::string& txt);
void Tick(void);
void Terminate(void);
int main(int argc, char* argv[])
{
    char* pbuf = new char[1024 * 1024 + 1];
    char* pbuf2 = new char[1024 * 1024 + 1];
    FILE* fp = fopen("test.txt", "rb");
    size_t size = fread(pbuf, 1, 1024 * 1024, fp);
    pbuf[size] = 0;
    DslParser::DslFile::Mac2Unix(pbuf, static_cast<int>(size));
    fclose(fp);
    char* p = pbuf;
    
    FILE* fp2 = fopen("test.h", "rb");
    size_t size2 = fread(pbuf2, 1, 1024 * 1024, fp2);
    pbuf2[size2] = 0;
    DslParser::DslFile::Mac2Unix(pbuf2, static_cast<int>(size2));
    fclose(fp2);
    char* p2 = pbuf2;

    if (size >= 3 && pbuf[0] == (char)0xef && pbuf[1] == (char)0xbb && pbuf[2] == (char)0xbf) {
        //skip utf-8 bom
        p += 3;
    }
    if (size >= 3 && pbuf2[0] == (char)0xef && pbuf2[1] == (char)0xbb && pbuf2[2] == (char)0xbf) {
        //skip utf-8 bom
        p2 += 3;
    }
    //DslParser::DslOptions::DontLoadComments(true);
    DslParser::DslStringAndObjectBufferT<>* pDslBuffer = new DslParser::DslStringAndObjectBufferT<>();
    {
        DslParser::DslFile dataFile(*pDslBuffer);
        //dataFile.EnableDebugInfo();
        dataFile.OnGetToken.attach([](const DslParser::DslTokenApi& api, char*& tok, short& val, int& line) {
            if (0 == strcmp(tok, "return")) {
                char* oldCurTok = api.getCurToken();
                char* oldLastTok = api.getLastToken(); 
                int index;
                char nc = api.peekNextValidChar(0, index);
                if (nc == '<' && api.peekChar(index + 1) == '-')
                    return false;
                api.setCurToken(const_cast<char*>("<-"));
                api.setLastToken(oldCurTok);
                api.enqueueToken(api.getCurToken(), api.getOperatorTokenValue(), line);
                api.setCurToken(oldCurTok);
                api.setLastToken(oldLastTok);
            }
            return true; 
            });
        dataFile.OnBeforeAddFunction.attach([](auto& api, auto* sd) {
            const char* pId = sd->GetFunctionId(0);
            if (sd->GetFunctionNum() > 0 && pId && 0 != strcmp(pId, "if")) {
                //在BeforeAddFunction回调里结束当前语句并开始一个新语句，效果上相当于给前一个函数加上分号
                //api.endStatement();
                //api.beginStatement();
            }
            return true;
            });
        dataFile.OnAddFunction.attach([](auto& api, auto* sd, auto* func) {
            //在AddFunction里一般不要修改程序结构，但可以修改添加函数的信息
            return true;
            });
        dataFile.OnBeforeEndStatement.attach([](auto& api) {
            //在BeforeEndStatement里可以修改程序结构，要符合dsl的语法语义流程
            return true;
            });
        dataFile.OnEndStatement.attach([](auto& api, auto*& sd) {
            //在EndStatement里一般不要修改程序结构，但可以修改或整体替换当前语句，在回调后会化简语句并添加到上一层语法构造中
            return true;
            });
        dataFile.Parse(p);

        FILE* fp3 = fopen("copy.txt", "wb");
        dataFile.WriteToFile(fp3, 0);
        fclose(fp3);
        FILE* fp4 = fopen("binary.txt", "wb");
        dataFile.SaveBinaryFile(fp4);
        fclose(fp4);
        DslParser::DslFile dataFile2(*pDslBuffer);
        FILE* fp5 = fopen("binary.txt", "rb");
        size_t size = fread(pbuf, 1, 1024 * 1024, fp5);
        fclose(fp5);
        std::vector<const char*> keys;
        std::vector<const char*> ids;
        dataFile2.LoadBinaryCode(pbuf, static_cast<int>(size), keys, ids);
        FILE* fp6 = fopen("unbinary.txt", "wb");
        dataFile2.WriteToFile(fp4, 0);
        fclose(fp6);

        DslData::DslFile file;
        Dsl::Transform(dataFile, file);
        FILE* dfp = fopen("copy2.txt", "wb");
        file.WriteToFile(dfp, 0);
        fclose(dfp);

        FILE* fp7 = fopen("binary2.txt", "wb");
        file.SaveBinaryFile(fp7);
        fclose(fp7);
        file.Reset();
        FILE* fp8 = fopen("binary2.txt", "rb");
        size_t size2 = fread(pbuf, 1, 1024 * 1024, fp8);
        fclose(fp8);
        std::vector<std::string> keys2;
        std::vector<std::string> ids2;
        file.LoadBinaryCode(pbuf, static_cast<int>(size2), keys2, ids2);
        dfp = fopen("unbinary2.txt", "wb");
        file.WriteToFile(dfp, 0);
        fclose(dfp);

        DslParser::DslFile dataFile3(*pDslBuffer);
        int len = 1024 * 1024;
        dataFile3.ParseGpp(p2, "={:=", "=:}=", pbuf, len);

        FILE* fp9 = fopen("test_gpp.h", "wb");
        dataFile3.WriteToFile(fp9, 0);
        fclose(fp9);
    }
    //brace脚本测试
    {
        pDslBuffer->Reset();
        DslParser::DslFile parsedFile(*pDslBuffer);
        std::ifstream ifs("brace.scp", std::ios_base::in);
        if (ifs.fail()) {
            printf("can't open brace.scp !\n");
            exit(-1);
        }
        ifs.read(pbuf, 1024 * 1024);
        pbuf[ifs.gcount()] = 0;
        parsedFile.Parse(pbuf);
        if (parsedFile.HasError()) {
            for (int i = 0; i < parsedFile.GetErrorNum(); ++i) {
                printf("[Brace Syntax]: %s", parsedFile.GetErrorInfo(i));
            }
        }
        else {
            DslData::DslFile dslFile;
            Dsl::Transform(parsedFile, dslFile);
            Brace::BraceScript script;
            script.OnInfo = [](auto str) { printf("[Brace Output]: %s\n", str.c_str()); };
            script.OnWarn = [](auto str) { printf("[Brace Warn]: %s\n", str.c_str()); };
            script.OnError = [](auto str) { printf("[Brace Error]: %s\n", str.c_str()); };
            script.LoadScript(dslFile);
            script.Run();

            Brace::FunctionExecutor funcExer(script);
            funcExer.Build("main");
            Brace::VarSetI64(*script.GlobalVariables(), funcExer.ArgInfo(0)->Type, funcExer.ArgInfo(0)->VarIndex, 345);
            Brace::VarSetF64(*script.GlobalVariables(), funcExer.ArgInfo(1)->Type, funcExer.ArgInfo(1)->VarIndex, 3.14);
            funcExer.Run();
            int64_t v = Brace::VarGetI64(*script.GlobalVariables(), funcExer.ResultInfo()->Type, funcExer.ResultInfo()->VarIndex);
            printf("FunctionExecutor result: %lld\n", v);
        }

        printf("Enter script:");
        std::string scp;
        std::getline(std::cin, scp);
        InitScript(pDslBuffer, scp);

        for (int i = 0; i < 100; ++i) {
            printf("Tick %d", i);
            Tick();
#ifdef __LINUX__
            ::usleep(100000);
#else
            ::Sleep(100);
#endif
        }
        Terminate();
    }
    delete[] pbuf;
    delete[] pbuf2;
    //必须在DslFile都释放后再释放DslStringAndObjectBuffer
    delete pDslBuffer;
    return 0;
}

class WaitExp final : public Brace::SimpleBraceApiBase
{
public:
    WaitExp(Brace::BraceScript& interpreter) :Brace::SimpleBraceApiBase(interpreter)
    {
    }
protected:
    virtual bool TypeInference(const Brace::ProcInfo& proc, const DslData::FunctionData& data, const std::vector<Brace::BraceApiLoadInfo>& argInfos, Brace::BraceApiLoadInfo& resultInfo) const override
    {
        for (auto& ali : argInfos) {
            if (ali.Type != Brace::BRACE_DATA_TYPE_INT32) {
                std::stringstream ss;
                ss << "wait's param must be int32 ! line: " << data.GetLine();
                LogError(ss.str());
                return false;
            }
        }
        resultInfo = Brace::BraceApiLoadInfo();
        return true;
    }
    virtual void Execute(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars, const std::vector<Brace::BraceApiLoadInfo>& argInfos)const override
    {
        auto sv = std::chrono::system_clock::now();

        for (auto& argInfo : argInfos) {
            if (argInfo.Type == Brace::BRACE_DATA_TYPE_INT32) {
                int v = (argInfo.IsGlobal ? gvars : lvars).NumericVars[argInfo.VarIndex].Int32Val;
                if (v <= 60000) {
                    auto cv = sv;
                    while (std::chrono::duration_cast<std::chrono::milliseconds>(cv - sv).count() < static_cast<long long>(v)) {
                        
                        CoroutineWithBoostContext::Detach();

                        cv = std::chrono::system_clock::now();
                    }
                    printf("wait finish.");
                }
            }
        }
    }
};

class ScriptEnv final
{
public:
    void SetScript(DslParser::IDslStringAndObjectBuffer* pBuffer, const std::string& txt) {
        m_pBuffer = pBuffer;
        m_pBraceScript = new Brace::BraceScript();
        m_pDslFile = new DslData::DslFile();
        m_pParsedFile = new DslParser::DslFile(*m_pBuffer);
        m_ScriptTxt = txt;
    }
    ~ScriptEnv(void)
    {
        if (nullptr != m_pBraceScript) {
            delete m_pBraceScript;
            m_pBraceScript = nullptr;
        }
        if (nullptr != m_pDslFile) {
            delete m_pDslFile;
            m_pDslFile = nullptr;
        }
        if (nullptr != m_pParsedFile) {
            delete m_pParsedFile;
            m_pParsedFile = nullptr;
        }
    }
public:
    void Run(void)
    {
        m_pBuffer->Reset();
        m_pParsedFile->Reset();
        m_pParsedFile->Parse(m_ScriptTxt.c_str());
        if (m_pParsedFile->HasError()) {
            for (int i = 0; i < m_pParsedFile->GetErrorNum(); ++i) {
                printf("[Brace Syntax]: %s", m_pParsedFile->GetErrorInfo(i));
            }
        }
        else {
            m_pDslFile->Reset();
            Dsl::Transform(*m_pParsedFile, *m_pDslFile);
            m_pBraceScript->Reset();
            m_pBraceScript->RegisterApi("wait", new Brace::BraceApiFactory<WaitExp>());
            m_pBraceScript->OnInfo = [](auto str) { printf("[Brace Output]: %s\n", str.c_str()); };
            m_pBraceScript->OnWarn = [](auto str) { printf("[Brace Warn]: %s\n", str.c_str()); };
            m_pBraceScript->OnError = [](auto str) { printf("[Brace Error]: %s\n", str.c_str()); };
            m_pBraceScript->LoadScript(*m_pDslFile);
            m_pBraceScript->Run();
        }
    }
private:
    DslParser::IDslStringAndObjectBuffer* m_pBuffer;
    Brace::BraceScript* m_pBraceScript;
    DslData::DslFile* m_pDslFile;
    DslParser::DslFile* m_pParsedFile;
    std::string m_ScriptTxt;
};
static ScriptEnv* g_ScriptEnv = nullptr;

class LongJmpRoutine1 : public CoroutineWithLongJmp::Coroutine
{
public:
    LongJmpRoutine1(int bufferSize) :CoroutineWithLongJmp::Coroutine(bufferSize)
    {}
protected:
    virtual void Routine(void) override
    {
        g_ScriptEnv->Run();
    }
};
class LongJmpRoutine2 : public CoroutineWithShareStack::Coroutine
{
public:
    LongJmpRoutine2(int bufferSize):CoroutineWithShareStack::Coroutine(bufferSize)
    {}
protected:
    virtual void Routine(void) override
    {
        g_ScriptEnv->Run();
    }
};
static LongJmpRoutine1* g_LongJmpRoutine1 = nullptr;
static LongJmpRoutine2* g_LongJmpRoutine2 = nullptr;

class BoostContextRoutine : public CoroutineWithBoostContext::Coroutine
{
public:
    BoostContextRoutine(int stackSize):CoroutineWithBoostContext::Coroutine(stackSize)
    {}
protected:
    virtual void Routine(void)override
    {
        g_ScriptEnv->Run();
    }
};
static BoostContextRoutine* g_BoostContextRoutine = nullptr;

void InitScript(DslParser::IDslStringAndObjectBuffer* pBuffer, const std::string& txt)
{
    if (nullptr == g_ScriptEnv) {
        g_ScriptEnv = new ScriptEnv();
    }
    if (nullptr == g_LongJmpRoutine1) {
        g_LongJmpRoutine1 = new LongJmpRoutine1(4 * 1024);
    }
    if (nullptr == g_LongJmpRoutine2) {
        g_LongJmpRoutine2 = new LongJmpRoutine2(1024*1024);
    }
    if (nullptr == g_BoostContextRoutine) {
        g_BoostContextRoutine = new BoostContextRoutine(1024*1024);
    }
    g_ScriptEnv->SetScript(pBuffer, txt);
}
void Tick(void)
{
    //g_LongJmpRoutine1->CallFromMain();
    //g_LongJmpRoutine2->CallFromMain();
    g_BoostContextRoutine->CallFromMain();
    //g_ScriptEnv->Run();
}
void Terminate(void)
{
    if (nullptr != g_LongJmpRoutine1) {
        delete g_LongJmpRoutine1;
        g_LongJmpRoutine1 = nullptr;
    }
    if (nullptr != g_LongJmpRoutine2) {
        delete g_LongJmpRoutine2;
        g_LongJmpRoutine2 = nullptr;
    }
    if (nullptr != g_BoostContextRoutine) {
        delete g_BoostContextRoutine;
        g_BoostContextRoutine = nullptr;
    }
    if (nullptr != g_ScriptEnv) {
        delete g_ScriptEnv;
        g_ScriptEnv = nullptr;
    }
}