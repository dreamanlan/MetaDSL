/*****************************************************************************

Dsl.cpp

******************************************************************************/
#include "Dsl.h"
#include "tsnprintf.h"

#if defined(__LINUX__)
#include <ctype.h>
#endif

#define GET_PRODUCTION_NAME    SlkGetProductionName
#define GET_SYMBOL_NAME        SlkGetSymbolName

namespace Dsl
{
  //------------------------------------------------------------------------------------------------------
  Call::Call(void) :ISyntaxComponent(ISyntaxComponent::TYPE_CALL),
    m_Params(0),
    m_ParamNum(0),
    m_ParamSpace(0),
    m_ParamClass(PARAM_CLASS_NOTHING)
  {
  }

  Call::~Call(void)
  {
    ReleaseParams();
  }

  Call::Call(const Call& other) :ISyntaxComponent(ISyntaxComponent::TYPE_CALL)
  {
    CopyFrom(other);
  }

  Call Call::operator=(const Call& other)
  {
    if (this == &other)
      return *this;
    ReleaseParams();
    CopyFrom(other);
    return *this;
  }

  void Call::CopyFrom(const Call& other)
  {
    m_Name = other.m_Name;
    m_ParamNum = other.m_ParamNum;
    m_ParamSpace = other.m_ParamSpace;
    m_ParamClass = other.m_ParamClass;
    m_Params = new SyntaxComponentPtr[m_ParamSpace];
    memcpy(m_Params, other.m_Params, m_ParamNum*sizeof(SyntaxComponentPtr));
  }

  void Call::PrepareParams(void)
  {
    if (NULL == m_Params && TRUE == HaveParam()) {
      m_Params = new SyntaxComponentPtr[DELTA_FUNCTION_PARAM];
      if (m_Params) {
        m_ParamSpace = DELTA_FUNCTION_PARAM;
      }
    } else if (HaveParam() && m_ParamNum >= m_ParamSpace) {
      int newSpace = m_ParamSpace + DELTA_FUNCTION_PARAM;
      if (newSpace <= MAX_FUNCTION_PARAM_NUM) {
        SyntaxComponentPtr* pNew = new SyntaxComponentPtr[newSpace];
        if (pNew) {
          memcpy(pNew, m_Params, m_ParamNum*sizeof(SyntaxComponentPtr));
          memset(pNew + m_ParamNum, 0, DELTA_FUNCTION_PARAM*sizeof(SyntaxComponentPtr));
          delete[] m_Params;
          m_Params = pNew;
          m_ParamSpace = newSpace;
        }
      }
    }
  }

  void Call::ReleaseParams(void)
  {
    if (NULL != m_Params) {
      delete[] m_Params;
      m_Params = NULL;
    }
  }

  Function::Function(DslFile& dataFile) :ISyntaxComponent(ISyntaxComponent::TYPE_FUNCTION),
    m_Statements(0),
    m_StatementNum(0),
    m_StatementSpace(0),
    m_ExtentClass(EXTENT_CLASS_NOTHING),
    m_ExternScript(0)
  {
    const ParserOptions& options = dataFile.GetOptions();
    m_MaxStatementNum = options.GetMaxStatementNum();
  }

  Function::~Function(void)
  {
    ReleaseStatements();
  }

  void Function::PrepareStatements(void)
  {
    if (NULL == m_Statements && TRUE == HaveStatement()) {
      m_Statements = new SyntaxComponentPtr[DELTA_FUNCTION_STATEMENT];
      if (m_Statements) {
        m_StatementSpace = DELTA_FUNCTION_STATEMENT;
      }
    } else if (HaveStatement() && m_StatementNum >= m_StatementSpace) {
      int newSpace = m_StatementSpace + DELTA_FUNCTION_STATEMENT;
      if (newSpace <= m_MaxStatementNum) {
        SyntaxComponentPtr* pNew = new SyntaxComponentPtr[newSpace];
        if (pNew) {
          memcpy(pNew, m_Statements, m_StatementNum*sizeof(SyntaxComponentPtr));
          memset(pNew + m_StatementNum, 0, DELTA_FUNCTION_STATEMENT*sizeof(SyntaxComponentPtr));
          delete[] m_Statements;
          m_Statements = pNew;
          m_StatementSpace = newSpace;
        }
      }
    }
  }

  void Function::ReleaseStatements(void)
  {
    if (NULL != m_Statements) {
      delete[] m_Statements;
      m_Statements = NULL;
    }
  }

  Statement::Statement(DslFile& dataFile) :ISyntaxComponent(ISyntaxComponent::TYPE_STATEMENT),
    m_Functions(0),
    m_FunctionNum(0),
    m_FunctionSpace(0)
  {
    const ParserOptions& options = dataFile.GetOptions();
    m_MaxFunctionNum = options.GetMaxFunctionDimensionNum();
  }

  void Statement::PrepareFunctions(void)
  {
    if (NULL == m_Functions) {
      m_Functions = new Function*[DELTA_STATEMENT_FUNCTION];
      if (m_Functions) {
        m_FunctionSpace = DELTA_STATEMENT_FUNCTION;
      }
    } else if (m_FunctionNum >= m_FunctionSpace) {
      int newSpace = m_FunctionSpace + DELTA_STATEMENT_FUNCTION;
      if (newSpace <= m_MaxFunctionNum) {
        Function** pNew = new Function*[newSpace];
        if (pNew) {
          memcpy(pNew, m_Functions, m_FunctionNum*sizeof(Function*));
          memset(pNew + m_FunctionNum, 0, DELTA_STATEMENT_FUNCTION*sizeof(Function*));
          delete[] m_Functions;
          m_Functions = pNew;
          m_FunctionSpace = newSpace;
        }
      }
    }
  }

  void Statement::ReleaseFunctions(void)
  {
    if (NULL != m_Functions) {
      delete[] m_Functions;
      m_Functions = NULL;
    }
  }

  void DslFile::AddStatement(Statement* p)
  {
    if (0 == p || 0 == m_DslInfos)
      return;
    if (m_DslInfoNum < 0 || m_DslInfoNum >= m_Options.GetMaxProgramSize())
      return;
    m_DslInfos[m_DslInfoNum] = p;
    ++m_DslInfoNum;
  }

  Value* DslFile::AddNewValueComponent(void)
  {
    Value* p = new Value();
    AddSyntaxComponent(p);
    return p;
  }

  Call* DslFile::AddNewCallComponent(void)
  {
    Call* p = new Call();
    AddSyntaxComponent(p);
    return p;
  }

  Function* DslFile::AddNewFunctionComponent(void)
  {
    Function* p = new Function(*this);
    AddSyntaxComponent(p);
    return p;
  }

  Statement* DslFile::AddNewStatementComponent(void)
  {
    Statement* p = new Statement(*this);
    AddSyntaxComponent(p);
    return p;
  }

  void DslFile::AddSyntaxComponent(ISyntaxComponent* p)
  {
    if (m_SyntaxComponentNum >= m_Options.GetSyntaxComponentPoolSize() || 0 == m_SyntaxComponentPool)
      return;
    m_SyntaxComponentPool[m_SyntaxComponentNum] = p;
    ++m_SyntaxComponentNum;
  }

  char* DslFile::AllocString(int len)
  {
    if (m_UnusedStringPtr + len - m_StringBuffer >= m_Options.GetStringBufferSize()) {
      return 0;
    }
    char* p = m_UnusedStringPtr;
    if (0 != p) {
      m_UnusedStringPtr[len] = 0;
      m_UnusedStringPtr += len + 1;
    }
    return p;
  }

  char* DslFile::AllocString(const char* src)
  {
    if (0 == src)
      return 0;
    int len = (int)strlen(src);
    char* p = AllocString(len);
    if (0 != p) {
      strcpy(p, src);
    }
    return p;
  }

  DslFile::DslFile(void) :m_IsDebugInfoEnable(FALSE),
    m_StringBuffer(NULL),
    m_UnusedStringPtr(NULL),
    m_SyntaxComponentPool(NULL),
    m_DslInfos(NULL)
  {
    Init();
  }

  DslFile::DslFile(const ParserOptions& options) :m_Options(options), m_IsDebugInfoEnable(FALSE),
    m_StringBuffer(NULL),
    m_UnusedStringPtr(NULL),
    m_SyntaxComponentPool(NULL),
    m_DslInfos(NULL)
  {
    Init();
  }

  DslFile::~DslFile(void)
  {
    Release();
  }

  void DslFile::Reset(void)
  {
    Release();
    Init();
  }

  void DslFile::Init(void)
  {
    m_StringBuffer = new char[m_Options.GetStringBufferSize()];
    m_UnusedStringPtr = m_StringBuffer;
    m_SyntaxComponentPool = new SyntaxComponentPtr[m_Options.GetSyntaxComponentPoolSize()];
    m_SyntaxComponentNum = 0;
    m_DslInfos = new StatementPtr[m_Options.GetMaxProgramSize()];
    m_DslInfoNum = 0;
    m_ErrorAndStringBuffer.Reset(m_StringBuffer, m_UnusedStringPtr, m_Options.GetStringBufferSize());
  }

  void DslFile::Release(void)
  {
    if (0 != m_StringBuffer) {
      delete[] m_StringBuffer;
      m_StringBuffer = 0;
      m_UnusedStringPtr = 0;
    }
    if (0 != m_SyntaxComponentPool) {
      for (int i = 0; i < m_SyntaxComponentNum; ++i) {
        if (0 != m_SyntaxComponentPool[i])
          delete m_SyntaxComponentPool[i];
      }
      delete[] m_SyntaxComponentPool;
      m_SyntaxComponentNum = 0;
    }
    if (0 != m_DslInfos) {
      delete[] m_DslInfos;
      m_DslInfoNum = 0;
    }
  }

  void ErrorAndStringBuffer::ClearErrorInfo(void)
  {
    m_HasError = FALSE;
    m_ErrorNum = 0;
    memset(m_ErrorInfo, 0, sizeof(m_ErrorInfo));
  }

  void ErrorAndStringBuffer::AddError(const char* error)
  {
    char* p = NewErrorInfo();
    if (p)
      tsnprintf(p, MAX_ERROR_INFO_CAPACITY, "%s", error);
  }

  //------------------------------------------------------------------------------------------------------------------------------------
  void WriteIndent(FILE* fp, int indent)
  {
    for (int i = 0; i < indent; ++i){
      fwrite("\t", 1, 1, fp);
    }
  }
  void WriteId(FILE* fp, const char* str, int indent)
  {
    WriteIndent(fp, indent);
    fprintf(fp, "%s", str);
  }
  void WriteString(FILE* fp, const char* str, int indent)
  {
    const char* escapeChars = " \t\r\n{}()[],;~`!%^&*-+=|:<>?/#\\";
    WriteIndent(fp, indent);
    fprintf(fp, "\"%s\"", str);
  }
  void WriteComponent(FILE* fp, ISyntaxComponent& component, int indent)
  {
    switch (component.GetSyntaxType()){
    case ISyntaxComponent::TYPE_VALUE:
      dynamic_cast<Value&>(component).WriteToFile(fp, indent);
      break;
    case ISyntaxComponent::TYPE_CALL:
      dynamic_cast<Call&>(component).WriteToFile(fp, indent);
      break;
    case ISyntaxComponent::TYPE_FUNCTION:
      dynamic_cast<Function&>(component).WriteToFile(fp, indent);
      break;
    case ISyntaxComponent::TYPE_STATEMENT:
      dynamic_cast<Statement&>(component).WriteToFile(fp, indent);
      break;
    }
  }
  //------------------------------------------------------------------------------------------------------------------------------------
  void Value::WriteToFile(FILE* fp, int indent)const
  {
#if _DEBUG
    if (IsString()){
      WriteString(fp, m_ConstStringVal, indent);
    } else {
      WriteId(fp, m_ConstStringVal, indent);
    }
#endif
  }
  void Call::WriteToFile(FILE* fp, int indent)const
  {
#if _DEBUG
    int paramClass = GetParamClass();
    if (paramClass == Call::PARAM_CLASS_OPERATOR){
      if (GetParamNum() == 2){
        ISyntaxComponent& component0 = *GetParam(0);
        WriteComponent(fp, component0, indent);
        fwrite(" ", 1, 1, fp);
        if (IsHighOrder() && NULL != m_Name.GetCall()){
          Call& call = *m_Name.GetCall();
          call.WriteToFile(fp, 0);
        } else {
          m_Name.WriteToFile(fp, 0);
        }
        fwrite(" ", 1, 1, fp);
        ISyntaxComponent& component1 = *GetParam(1);
        WriteComponent(fp, component1, 0);
      } else {
        fwrite(" ", 1, 1, fp);
        if (IsHighOrder() && NULL != m_Name.GetCall()){
          Call& call = *m_Name.GetCall();
          call.WriteToFile(fp, 0);
        } else {
          m_Name.WriteToFile(fp, 0);
        }
        fwrite(" ", 1, 1, fp);
        ISyntaxComponent& component0 = *GetParam(0);
        WriteComponent(fp, component0, indent);
      }
    } else {
      if (IsHighOrder() && NULL != m_Name.GetCall()){
        Call& call = *m_Name.GetCall();
        call.WriteToFile(fp, indent);
      } else {
        m_Name.WriteToFile(fp, indent);
      }
      if (HaveParam()){
        switch (paramClass){
        case Call::PARAM_CLASS_PARENTHESIS:
          fwrite("(", 1, 1, fp);
          break;
        case Call::PARAM_CLASS_BRACKET:
          fwrite("[", 1, 1, fp);
          break;
        case Call::PARAM_CLASS_PERIOD:
          fwrite(".", 1, 1, fp);
          break;
        case Call::PARAM_CLASS_PERIOD_PARENTHESIS:
          fwrite(".(", 1, 1, fp);
          break;
        case Call::PARAM_CLASS_PERIOD_BRACKET:
          fwrite(".[", 1, 1, fp);
          break;
        case Call::PARAM_CLASS_PERIOD_BRACE:
          fwrite(".{", 1, 1, fp);
          break;
        }
        for (int ix = 0; ix < GetParamNum(); ++ix){
          if (ix > 0){
            fwrite(",", 1, 1, fp);
          }
          ISyntaxComponent& component = *GetParam(ix);
          WriteComponent(fp, component, 0);
        }
        switch (paramClass){
        case Call::PARAM_CLASS_PARENTHESIS:
          fwrite(")", 1, 1, fp);
          break;
        case Call::PARAM_CLASS_BRACKET:
          fwrite("]", 1, 1, fp);
          break;
        case Call::PARAM_CLASS_PERIOD:
          break;
        case Call::PARAM_CLASS_PERIOD_PARENTHESIS:
          fwrite(")", 1, 1, fp);
          break;
        case Call::PARAM_CLASS_PERIOD_BRACKET:
          fwrite("]", 1, 1, fp);
          break;
        case Call::PARAM_CLASS_PERIOD_BRACE:
          fwrite("}", 1, 1, fp);
          break;
        }
      }
    }
#endif
  }
  void Function::WriteToFile(FILE* fp, int indent)const
  {
#if _DEBUG
    if (m_Call.IsValid()){
      m_Call.WriteToFile(fp, indent);
      fwrite("\n", 1, 1, fp);
    }
    if (HaveStatement()){
      WriteIndent(fp, indent);
      fwrite("{\n", 2, 1, fp);
      for (int ix = 0; ix < GetStatementNum(); ++ix){
        ISyntaxComponent& component = *GetStatement(ix);
        WriteComponent(fp, component, indent + 1);
        fwrite(";\n", 2, 1, fp);
      }
      WriteIndent(fp, indent);
      fwrite("}", 1, 1, fp);
    }
    if (HaveExternScript()){
      WriteIndent(fp, indent);
      fwrite("{:\n", 3, 1, fp);
      fwrite(m_ExternScript, strlen(m_ExternScript), 1, fp);
      fwrite(":}", 2, 1, fp);
    }
#endif
  }
  void Statement::WriteToFile(FILE* fp, int indent)const
  {
#if _DEBUG
    int num = GetFunctionNum();
    Function* func1 = GetFunction(0);
    Function* func2 = GetFunction(1);
    if (num == 2 && NULL != func1 && NULL != func2 && func1->GetCall().GetParamClass() == Call::PARAM_CLASS_TERNARY_OPERATOR && func2->GetCall().GetParamClass() == Call::PARAM_CLASS_TERNARY_OPERATOR){
      ISyntaxComponent* pcomp0 = func1->GetCall().GetParam(0);
      ISyntaxComponent* pcomp1 = func1->GetStatement(0);
      ISyntaxComponent* pcomp2 = func2->GetStatement(0);
      if (NULL!=pcomp0 && NULL != pcomp1 && NULL != pcomp2){
        WriteComponent(fp, *pcomp0, indent);
        fwrite(" ? ", 3, 1, fp);
        WriteComponent(fp, *pcomp1, 0);
        fwrite(" : ", 3, 1, fp);
        WriteComponent(fp, *pcomp2, 0);
      }
    } else {
      for (int ix = 0; ix < num; ++ix){
        ISyntaxComponent& component = *GetFunction(ix);
        WriteComponent(fp, component, indent);
        if (ix < num - 1){
          fwrite("\n", 1, 1, fp);
        }
      }
    }
#endif
  }
  void DslFile::WriteToFile(FILE* fp, int indent)const
  {
#if _DEBUG
    for (int ix = 0; ix < GetDslInfoNum(); ++ix){
      Statement* pStatement = GetDslInfo(ix);
      if (pStatement){
        pStatement->WriteToFile(fp, indent);
        fwrite(";\n", 2, 1, fp);
      }
    }
#endif
  }
}