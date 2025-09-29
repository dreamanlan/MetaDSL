﻿#include "BaseType.h"
#include "Dsl.h"
#include "ScriptableDslHelper.h"
#include "BraceScript.h"
#include "SimpleCoroutine.h"
#include "ShareStackCoroutine.h"
#include "BraceCoroutine.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>

static std::chrono::time_point<std::chrono::high_resolution_clock> g_start_time_point;

void InitScript(DslParser::IDslStringAndObjectBuffer* pBuffer, const std::string& txt);
void Tick();
void Terminate();
int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    g_start_time_point = std::chrono::high_resolution_clock::now();

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

    if (size >= 3 && pbuf[0] == '\xef' && pbuf[1] == '\xbb' && pbuf[2] == '\xbf') {
        //skip utf-8 bom
        p += 3;
    }
    if (size >= 3 && pbuf2[0] == '\xef' && pbuf2[1] == '\xbb' && pbuf2[2] == '\xbf') {
        //skip utf-8 bom
        p2 += 3;
    }
    //DslParser::DslOptions::DontLoadComments(true);
    DslParser::DslStringAndObjectBufferT<>* pDslBuffer = new DslParser::DslStringAndObjectBufferT<>();
    {
        DslParser::DslFile dataFile(*pDslBuffer);
        ScriptableDslHelper::ForBraceScript().SetCallbacks(dataFile);
        //dataFile.EnableDebugInfo();
        /*
        dataFile.OnGetToken.attach([]([[maybe_unused]] const DslParser::DslActionApi& actionApi, const DslParser::DslTokenApi& tokenApi, char*& tok, [[maybe_unused]] short& val, int& line) {
            if (0 == strcmp(tok, "return")) {
                char* oldCurTok = tokenApi.getCurToken();
                char* oldLastTok = tokenApi.getLastToken(); 
                int index;
                char nc = tokenApi.peekNextValidChar(0, index);
                if (nc == '<' && tokenApi.peekChar(index + 1) == '-')
                    return false;
                tokenApi.setCurToken(const_cast<char*>("<-"));
                tokenApi.setLastToken(oldCurTok);
                tokenApi.enqueueToken(tokenApi.getCurToken(), tokenApi.getOperatorTokenValue(), line);
                tokenApi.setCurToken(oldCurTok);
                tokenApi.setLastToken(oldLastTok);
            }
            return true; 
            });
        dataFile.OnBeforeAddFunction.attach([](auto& api, auto* sd) {
            (void)api;
            const char* pId = sd->GetFunctionId(0);
            if (sd->GetFunctionNum() > 0 && pId && 0 != strcmp(pId, "if")) {
                //End the current statement and start a new statement in the BeforeAddFunction callback.
                //The effect is equivalent to adding a semicolon to the previous function.
                //api.endStatement();
                //api.beginStatement();
            }
            return true;
            });
        dataFile.OnAddFunction.attach([](auto& api, auto* sd, auto* func) {
            (void)api, (void)sd, (void)func;
            //Generally, you should not modify the program structure in AddFunction, but you can modify the information about the added function.
            return true;
            });
        dataFile.OnBeforeEndStatement.attach([](auto& api, auto* sd) {
            (void)api, (void)sd;
            //The program structure can be modified in BeforeEndStatement, and it must comply with the syntax and semantic process of DSL.
            return true;
            });
        dataFile.OnEndStatement.attach([](auto& api, auto*& sd) {
            (void)api, (void)sd;
            //Generally, the program structure should not be modified in EndStatement, but the current statement can be modified or replaced as a whole.
            //After the callback, the statement will be simplified and added to the upper level syntax structure.
            return true;
            });
        */
        dataFile.Parse(p);

        FILE* fp3 = fopen("copy.txt", "wb");
        dataFile.WriteToFile(fp3, 0);
        fclose(fp3);
        FILE* fp4 = fopen("binary.txt", "wb");
        dataFile.SaveBinaryFile(fp4);
        fclose(fp4);
        DslParser::DslFile dataFile2(*pDslBuffer);
        FILE* fp5 = fopen("binary.txt", "rb");
        size_t size3 = fread(pbuf, 1, 1024 * 1024, fp5);
        fclose(fp5);
        std::vector<const char*> keys;
        std::vector<const char*> ids;
        dataFile2.LoadBinaryCode(pbuf, static_cast<int>(size3), keys, ids);
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
        size_t size4 = fread(pbuf, 1, 1024 * 1024, fp8);
        fclose(fp8);
        std::vector<std::string> keys2;
        std::vector<std::string> ids2;
        file.LoadBinaryCode(pbuf, static_cast<int>(size4), keys2, ids2);
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
    //brace script test
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
            funcExer.Run(*script.GlobalVariables(), *script.GlobalVariables());
            int64_t v = Brace::VarGetI64(*script.GlobalVariables(), funcExer.ResultInfo()->Type, funcExer.ResultInfo()->VarIndex);
            printf("FunctionExecutor result: %lld\n", static_cast<long long>(v));
        }
        //------
        std::cout << "DataTypeInfo:" << sizeof(Brace::DataTypeInfo) << std::endl;
        std::cout << "RegisterInfo:" << sizeof(Brace::RegisterInfo) << std::endl;
        std::cout << "ParamTypeInfo:" << sizeof(Brace::ParamTypeInfo) << std::endl;
        std::cout << "OperandTypeInfo:" << sizeof(Brace::OperandTypeInfo) << std::endl;
        std::cout << "VarInfo:" << sizeof(Brace::VarInfo) << std::endl;
        std::cout << "ParamRetInfo:" << sizeof(Brace::ParamRetInfo) << std::endl;
        std::cout << "OperandLoadtimeInfo:" << sizeof(Brace::OperandLoadtimeInfo) << std::endl;
        std::cout << "OperandRuntimeInfo:" << sizeof(Brace::OperandRuntimeInfo) << std::endl;
        std::cout << "ReferenceInfo:" << sizeof(Brace::ReferenceInfo) << std::endl;
        std::cout << "NumericValue:" << sizeof(Brace::NumericValue) << std::endl;
        std::cout << "VariableInfo:" << sizeof(Brace::VariableInfo) << std::endl;
        std::cout << "FuncApiTypeInfo:" << sizeof(Brace::FuncApiTypeInfo) << std::endl;
        std::cout << "Instruction:" << sizeof(Brace::Instruction) << std::endl;
        std::cout << "FuncInfo:" << sizeof(Brace::FuncInfo) << std::endl;
        std::cout << "RuntimeStackInfo:" << sizeof(Brace::RuntimeStackInfo) << std::endl;

        //------
        printf("Enter script:");
        std::string scp;
        std::getline(std::cin, scp);
        InitScript(pDslBuffer, scp);
        Tick();
        ///*
        for (int i = 0; i < 100; ++i) {
            printf("Tick %d", i);
            Tick();
#ifdef __LINUX__
            ::usleep(100000);
#else
            ::Sleep(100);
#endif
        }
        //*/
        Terminate();
        CoroutineWithBoostContext::TryRelease();
        std::size_t count = 0;
        std::size_t alloced_size = 0;
        std::size_t pooled_size = CoroutineWithBoostContext::StatMemory(count, alloced_size);
        printf("\nmemory: %u pooled size: %u alloced size: %u\n", count, pooled_size, alloced_size);
    }
    delete[] pbuf;
    delete[] pbuf2;
    //DslStringAndObjectBuffer must be released after all DslFiles are released.
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
    virtual bool TypeInference([[maybe_unused]] const Brace::FuncInfo& func, const DslData::FunctionData& data, const std::vector<Brace::OperandLoadtimeInfo>& argInfos, Brace::OperandLoadtimeInfo& resultInfo) override
    {
        for (auto&& ali : argInfos) {
            if (ali.Type != Brace::BRACE_DATA_TYPE_INT32) {
                std::stringstream ss;
                ss << "wait's param must be int32 ! line: " << data.GetLine();
                LogError(ss.str());
                return false;
            }
        }
        resultInfo = Brace::OperandLoadtimeInfo();
        return true;
    }
    virtual void Execute(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars, const std::vector<Brace::OperandRuntimeInfo>& argInfos, [[maybe_unused]] const Brace::OperandRuntimeInfo& resultInfo)const override
    {
        auto sv = std::chrono::system_clock::now();

        for (auto&& argInfo : argInfos) {
            if (argInfo.Type == Brace::BRACE_DATA_TYPE_INT32) {
                int v = (argInfo.IsGlobal ? gvars : lvars).NumericVars[argInfo.VarIndex].Int32Val;
                if (v <= 60000) {
                    auto cv = sv;
                    while (std::chrono::duration_cast<std::chrono::milliseconds>(cv - sv).count() < static_cast<long long>(v)) {
                        
                        //CoroutineWithLongJmp::Detach();
                        //CoroutineWithShareStack::Detach();
                        CoroutineWithBoostContext::TryYield();

                        cv = std::chrono::system_clock::now();
                    }
                    printf("wait finish.");
                }
            }
        }
    }
};
class TimeExp final : public Brace::SimpleBraceApiBase
{
public:
    TimeExp(Brace::BraceScript& interpreter) :Brace::SimpleBraceApiBase(interpreter)
    {
    }
protected:
    virtual bool TypeInference([[maybe_unused]] const Brace::FuncInfo& func, [[maybe_unused]] const DslData::FunctionData& data, [[maybe_unused]] const std::vector<Brace::OperandLoadtimeInfo>& argInfos, Brace::OperandLoadtimeInfo& resultInfo) override
    {
        resultInfo.Type = Brace::BRACE_DATA_TYPE_UINT64;
        resultInfo.ObjectTypeId = Brace::PREDEFINED_BRACE_OBJECT_TYPE_NOTOBJ;
        resultInfo.Name = GenTempVarName();
        resultInfo.VarIndex = AllocVariable(resultInfo.Name, resultInfo.Type, resultInfo.ObjectTypeId);
        return true;
    }
    virtual void Execute(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars, [[maybe_unused]] const std::vector<Brace::OperandRuntimeInfo>& argInfos, const Brace::OperandRuntimeInfo& resultInfo)const override
    {
        auto cv = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = cv - g_start_time_point;
        auto tv = static_cast<uint64_t>(diff.count() * 1000'000);
        Brace::VarSetUInt64((resultInfo.IsGlobal ? gvars : lvars), resultInfo.VarIndex, tv);
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
public:
    ScriptEnv():m_pBuffer(nullptr), m_pBraceScript(nullptr), m_pDslFile(nullptr), m_pParsedFile(nullptr)
    {}
    ~ScriptEnv()
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
    void Run()
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
            m_pBraceScript->RegisterApi("wait", "wait api", new Brace::BraceApiFactory<WaitExp>());
            m_pBraceScript->RegisterApi("time", "time api", new Brace::BraceApiFactory<TimeExp>());
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
    virtual void Routine() override
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
    virtual void Routine() override
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
    virtual void Routine()override
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
        //CoroutineWithLongJmp::TryInit();
        g_LongJmpRoutine1 = new LongJmpRoutine1(4 * 1024);
    }
    if (nullptr == g_LongJmpRoutine2) {
        //CoroutineWithShareStack::TryInit(1024 * 1024);
        g_LongJmpRoutine2 = new LongJmpRoutine2(1024*1024);
    }
    if (nullptr == g_BoostContextRoutine) {
        CoroutineWithBoostContext::TryInit();
        g_BoostContextRoutine = new BoostContextRoutine(1024*1024);
    }
    g_ScriptEnv->SetScript(pBuffer, txt);
}
void Tick()
{
    //g_LongJmpRoutine1->Call();
    //g_LongJmpRoutine2->Call();
    g_BoostContextRoutine->TryStart();
    CoroutineWithBoostContext::TryYield();
    //g_ScriptEnv->Run();
}
void Terminate()
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