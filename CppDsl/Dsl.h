/*****************************************************************************

calc.h

******************************************************************************/

#ifndef _CALC_H
#define _CALC_H

#include "Type.h"
#include "Queue.h"
#include "Hashtable.h"

namespace Dsl
{
  template<typename DestT>
  struct ReinterpretCast
  {
    template<typename SrcT>
    static DestT From(const SrcT& v)
    {
      union
      {
        SrcT	m_Src;
        DestT	m_Dest;
      } tmp;
      tmp.m_Src = v;
      return tmp.m_Dest;
    }
  };

  enum
  {
    MAX_ERROR_INFO_CAPACITY = 256,
    MAX_RECORD_ERROR_NUM = 16,
    MAX_FUNCTION_PARAM_NUM = 32,

    DELTA_FUNCTION_PARAM = 2,
    DELTA_FUNCTION_STATEMENT = 8,
    DELTA_STATEMENT_FUNCTION = 1,
  };

  enum
  {
    MAX_FUNCTION_DIMENSION_NUM = 8,
    MAX_STATEMENT_NUM = 1024,
    MAX_PROGRAM_SIZE = 16 * 1024,
    STRING_BUFFER_SIZE = 1024 * 1024,
    SYNTAXCOMPONENT_POOL_SIZE = 16 * 1024,
  };

  class ParserOptions
  {
  public:
    ParserOptions(void) :
      m_MaxFunctionDimensionNum(MAX_FUNCTION_DIMENSION_NUM),
      m_MaxStatementNum(MAX_STATEMENT_NUM),
      m_MaxProgramSize(MAX_PROGRAM_SIZE),
      m_StringBufferSize(STRING_BUFFER_SIZE),
      m_SyntaxComponentPoolSize(SYNTAXCOMPONENT_POOL_SIZE)
    {}
  public:
    INT GetMaxFunctionDimensionNum() const { return m_MaxFunctionDimensionNum; }
    void SetMaxFunctionDimensionNum(INT val) { m_MaxFunctionDimensionNum = val; }
    INT GetMaxStatementNum() const { return m_MaxStatementNum; }
    void SetMaxStatementNum(INT val) { m_MaxStatementNum = val; }
    INT GetMaxProgramSize() const { return m_MaxProgramSize; }
    void SetMaxProgramSize(INT val) { m_MaxProgramSize = val; }
    INT GetStringBufferSize() const { return m_StringBufferSize; }
    void SetStringBufferSize(INT val) { m_StringBufferSize = val; }
    INT GetSyntaxComponentPoolSize(void) const { return m_SyntaxComponentPoolSize; }
    void SetSyntaxComponentPoolSize(INT val) { m_SyntaxComponentPoolSize = val; }
  private:
    INT	m_MaxFunctionDimensionNum;
    INT	m_MaxStatementNum;
    INT	m_MaxProgramSize;
    INT	m_StringBufferSize;
    INT m_SyntaxComponentPoolSize;
  };

  class ISyntaxComponent
  {
  public:
    enum
    {
      TYPE_NULL,
      TYPE_VALUE,
      TYPE_CALL,
      TYPE_FUNCTION,
      TYPE_STATEMENT,
    };
  public:
    ISyntaxComponent(INT syntaxType) :mSyntaxType(syntaxType){}
    virtual ~ISyntaxComponent(void){}
  public:
    virtual BOOL IsValid(void) const = 0;
    virtual const CHAR* GetId(void) const = 0;
    virtual INT GetIdType(void) const = 0;
    virtual INT GetLine(void) const = 0;
    virtual void WriteToFile(FILE* fp, int indent) const = 0;
  public:
    INT GetSyntaxType(void) const { return mSyntaxType; }
  protected:
    INT mSyntaxType;
  };

  class Call;
  class Value : public ISyntaxComponent
  {
  public:
    enum
    {
      TYPE_INVALID = -1,
      TYPE_INT = 0,
      TYPE_FLOAT,
      TYPE_STRING,
      TYPE_VARIABLE_NAME,
      TYPE_CALL,
    };

    Value(void) :ISyntaxComponent(ISyntaxComponent::TYPE_VALUE), m_Type(TYPE_INVALID), m_StringVal(0), m_Line(0){}
    explicit Value(CHAR* val) :ISyntaxComponent(ISyntaxComponent::TYPE_VALUE), m_Type(TYPE_STRING), m_StringVal(val), m_Line(0){}
    explicit Value(const CHAR* val) :ISyntaxComponent(ISyntaxComponent::TYPE_VALUE), m_Type(TYPE_STRING), m_ConstStringVal(val), m_Line(0){}
    explicit Value(Call* val) :ISyntaxComponent(ISyntaxComponent::TYPE_VALUE), m_Type(TYPE_CALL), m_Call(val), m_Line(0){}
    explicit Value(CHAR* val, INT type) :ISyntaxComponent(ISyntaxComponent::TYPE_VALUE), m_Type(type), m_StringVal(val), m_Line(0){}
    explicit Value(const CHAR* val, INT type) :ISyntaxComponent(ISyntaxComponent::TYPE_VALUE), m_Type(type), m_ConstStringVal(val), m_Line(0){}
    Value(const Value& other) :ISyntaxComponent(ISyntaxComponent::TYPE_VALUE), m_Type(TYPE_INVALID), m_StringVal(0), m_Line(0)
    {
      CopyFrom(other);
    }
    Value& operator=(const Value& other)
    {
      if (this == &other)
        return *this;
      CopyFrom(other);
      return *this;
    }

    virtual BOOL IsValid(void)const{ return (m_Type != TYPE_INVALID ? TRUE : FALSE); }
    virtual INT GetIdType(void)const{ return m_Type; }
    virtual const CHAR* GetId(void)const{ return m_StringVal; }
    virtual INT GetLine(void)const{ return m_Line; }
    virtual void WriteToFile(FILE* fp, int indent) const;

    Call* GetCall(void)const{ return m_Call; }

    BOOL IsInt(void)const{ return (m_Type == TYPE_INT ? TRUE : FALSE); }
    BOOL IsFloat(void)const{ return (m_Type == TYPE_FLOAT ? TRUE : FALSE); }
    BOOL IsString(void)const{ return (m_Type == TYPE_STRING ? TRUE : FALSE); }
    BOOL IsVariableName(void)const{ return (m_Type == TYPE_VARIABLE_NAME ? TRUE : FALSE); }
    BOOL IsCall(void)const{ return (m_Type == TYPE_CALL ? TRUE : FALSE); }
    
    void SetInvalid(void)
    {
      m_Type = TYPE_INVALID;
      m_StringVal = 0;
    }
    void SetInt(CHAR* str)
    {
      m_Type = TYPE_INT;
      m_StringVal = str;
    }
    void SetInt(const CHAR* str)
    {
      m_Type = TYPE_INT;
      m_ConstStringVal = str;
    }
    void SetFloat(CHAR* str)
    {
      m_Type = TYPE_FLOAT;
      m_StringVal = str;
    }
    void SetFloat(const CHAR* str)
    {
      m_Type = TYPE_FLOAT;
      m_ConstStringVal = str;
    }
    void SetString(CHAR* str)
    {
      m_Type = TYPE_STRING;
      m_StringVal = str;
    }
    void SetString(const CHAR* str)
    {
      m_Type = TYPE_STRING;
      m_ConstStringVal = str;
    }
    void SetCall(Call* func)
    {
      m_Type = TYPE_CALL;
      m_Call = func;
    }
    void SetVariableName(CHAR* name)
    {
      m_Type = TYPE_VARIABLE_NAME;
      m_StringVal = name;
    }
    void SetLine(INT line)
    {
      m_Line = line;
    }
  private:
    void CopyFrom(const Value& other)
    {
      m_Type = other.m_Type;
      m_StringVal = other.m_StringVal;
      m_Line = other.m_Line;
    }
  private:
    INT					  m_Type;
    union
    {
      CHAR*			  m_StringVal;
      const CHAR*	m_ConstStringVal;//在脚本里与m_StringVal类型相同,用于实现自动const_cast
      Call*	      m_Call;
    };
    INT           m_Line;
  public:
    static Value& GetInvalidValueRef(void)
    {
      static Value s_Val;
      s_Val.SetInvalid();
      return s_Val;
    }
  };

  class NullSyntax : public ISyntaxComponent
  {
  public:
    NullSyntax(void) : ISyntaxComponent(ISyntaxComponent::TYPE_NULL){}
  public:
    virtual BOOL IsValid(void) const { return FALSE; }
    virtual const CHAR* GetId(void) const { return ""; }
    virtual INT GetIdType(void) const { return Value::TYPE_INVALID; }
    virtual INT GetLine(void) const { return 0; }
    virtual void WriteToFile(FILE* fp, int indent) const {}
  public:
    static NullSyntax& GetNullSyntaxRef()
    {
      static NullSyntax s_Instance;
      return s_Instance;
    }
  };

  class Call : public ISyntaxComponent
  {
  public:
    enum
    {
      PARAM_CLASS_NOTHING = 0,
      PARAM_CLASS_PARENTHESIS,
      PARAM_CLASS_BRACKET,
      PARAM_CLASS_PERIOD,
      PARAM_CLASS_PERIOD_PARENTHESIS,
      PARAM_CLASS_PERIOD_BRACKET,
      PARAM_CLASS_PERIOD_BRACE,
      PARAM_CLASS_OPERATOR,
      PARAM_CLASS_TERNARY_OPERATOR,
    };
    typedef ISyntaxComponent* SyntaxComponentPtr;
  public:
    virtual BOOL IsValid(void)const
    {
      if (HaveName())
        return TRUE;
      else if (HaveParam())
        return TRUE;
      else
        return FALSE;
    }
    virtual INT GetIdType(void)const{ return m_Name.GetIdType(); }
    virtual const CHAR* GetId(void)const{ return m_Name.GetId(); }
    virtual INT GetLine(void)const{ return m_Name.GetLine(); }
    virtual void WriteToFile(FILE* fp, int indent) const;
  public:
    void		SetName(const Value& val){ m_Name = val; }
    Value&	GetName(void){ return m_Name; }
    void		ClearParams(void){ m_ParamNum = 0; }
    void		AddParam(ISyntaxComponent*	pVal)
    {
      if (0 == pVal || m_ParamNum < 0 || m_ParamNum >= MAX_FUNCTION_PARAM_NUM)
        return;
      PrepareParams();
      if (0 == m_Params || m_ParamNum >= m_ParamSpace)
        return;
      m_Params[m_ParamNum] = pVal;
      ++m_ParamNum;
    }
    void    SetParam(int index, ISyntaxComponent* pVal)
    {
      if (NULL == pVal || index < 0 || index >= MAX_FUNCTION_PARAM_NUM)
        return;
      m_Params[index] = pVal;
    }
    void		SetParamClass(INT v){ m_ParamClass = v; }
    INT		  GetParamClass(void)const{ return m_ParamClass; }
    BOOL		HaveName(void)const{ return m_Name.IsValid(); }
    BOOL		HaveParam(void)const{ return m_ParamClass != PARAM_CLASS_NOTHING; }
    BOOL    IsHighOrder(void)const{ return m_Name.IsCall(); }
  public:
    const Value&	GetName(void)const{ return m_Name; }
    INT			GetParamNum(void)const{ return m_ParamNum; }
    ISyntaxComponent*	GetParam(INT index)const
    {
      if (0 == m_Params || index < 0 || index >= m_ParamNum || index >= MAX_FUNCTION_PARAM_NUM)
        return 0;
      return m_Params[index];
    }
  public:
    Call(void);
    virtual ~Call(void);
    Call(const Call& other);
    Call operator=(const Call& other);
  private:
    void          CopyFrom(const Call& other);
    void          PrepareParams(void);
    void          ReleaseParams(void);
  private:
    Value			          m_Name;
    ISyntaxComponent**	m_Params;
    INT				          m_ParamNum;
    INT				          m_ParamSpace;
    INT				          m_ParamClass;
  public:
    static Call*& GetNullCallPtrRef(void)
    {
      static Call* s_P = 0;
      return s_P;
    }
  };

  class DslFile;
  class Function : public ISyntaxComponent
  {
  public:
    enum
    {
      EXTENT_CLASS_NOTHING = 0,
      EXTENT_CLASS_STATEMENT,
      EXTENT_CLASS_EXTERN_SCRIPT,
    };
    typedef ISyntaxComponent* SyntaxComponentPtr;
  public:
    virtual BOOL IsValid(void)const
    {
      if (m_Call.IsValid())
        return TRUE;
      else if (HaveStatement() || HaveExternScript())
        return TRUE;
      else
        return FALSE;
    }
    virtual INT GetIdType(void)const{ return m_Call.GetIdType(); }
    virtual const CHAR* GetId(void)const{ return m_Call.GetId(); }
    virtual INT GetLine(void)const{ return m_Call.GetLine(); }
    virtual void WriteToFile(FILE* fp, int indent) const;
  public:
    void		SetCall(const Call& val){ m_Call = val; }
    Call&	  GetCall(void){ return m_Call; }
    void		ClearStatements(void){ m_StatementNum = 0; }
    void		AddStatement(ISyntaxComponent* pVal)
    {
      if (0 == pVal || m_StatementNum < 0 || m_StatementNum >= m_MaxStatementNum)
        return;
      PrepareStatements();
      if (0 == m_Statements || m_StatementNum >= m_StatementSpace)
        return;
      m_Statements[m_StatementNum] = pVal;
      ++m_StatementNum;
    }
    void    SetStatement(int index, ISyntaxComponent* pVal)
    {
      if (NULL == pVal || index < 0 || index >= m_MaxStatementNum)
        return;
      m_Statements[index] = pVal;
    }
    void		SetExternScript(const CHAR* scp){ m_ExternScript = scp; }
    void		SetExtentClass(INT v){ m_ExtentClass = v; }
    INT		  GetExtentClass(void)const{ return m_ExtentClass; }
    BOOL		HaveStatement(void)const{ return m_ExtentClass == EXTENT_CLASS_STATEMENT; }
    BOOL		HaveExternScript(void)const{ return m_ExtentClass == EXTENT_CLASS_EXTERN_SCRIPT; }
  public:
    const Call&	GetCall(void)const{ return m_Call; }
    INT			    GetStatementNum(void)const{ return m_StatementNum; }
    ISyntaxComponent*	GetStatement(INT index)const
    {
      if (0 == m_Statements || index < 0 || index >= m_StatementNum || index >= m_MaxStatementNum)
        return 0;
      return m_Statements[index];
    }
    const CHAR*	GetExternScript(void)const{ return m_ExternScript; }
  public:
    Function(DslFile& dataFile);
    virtual ~Function(void);
  private:
    void          PrepareStatements(void);
    void          ReleaseStatements(void);
  private:
    Call			          m_Call;
    ISyntaxComponent**  m_Statements;
    INT				          m_StatementNum;
    INT				          m_StatementSpace;
    INT				          m_MaxStatementNum;
    const CHAR*		      m_ExternScript;
    INT				          m_ExtentClass;
  public:
    static Function*& GetNullFunctionPtrRef(void)
    {
      static Function* s_P = 0;
      return s_P;
    }
  };

  class Statement : public ISyntaxComponent
  {
  public:
    virtual BOOL IsValid(void)const
    {
      if (NULL != m_Functions && m_FunctionNum > 0 && m_Functions[0]->IsValid())
        return TRUE;
      else
        return FALSE;
    }
    virtual INT GetIdType(void)const
    {
      INT type = Value::TYPE_INVALID;
      if (IsValid()) {
        type = m_Functions[0]->GetIdType();
      }
      return type;
    }
    virtual const CHAR* GetId(void)const
    {
      const CHAR* str = "";
      if (IsValid()) {
        str = m_Functions[0]->GetId();
      }
      return str;
    }
    virtual INT GetLine(void)const
    {
      INT line = 0;
      if (IsValid()) {
        line = m_Functions[0]->GetLine();
      }
      return line;
    }
    virtual void WriteToFile(FILE* fp, int indent) const;
  public:
    void		ClearFunctions(void){ m_FunctionNum = 0; }
    void		AddFunction(Function* pVal)
    {
      if (NULL == pVal || m_FunctionNum < 0 || m_FunctionNum >= m_MaxFunctionNum)
        return;
      PrepareFunctions();
      if (NULL == m_Functions || m_FunctionNum >= m_FunctionSpace)
        return;
      m_Functions[m_FunctionNum] = pVal;
      ++m_FunctionNum;
    }
    Function*&	GetLastFunctionRef(void)const
    {
      if (NULL == m_Functions || 0 == m_FunctionNum)
        return Function::GetNullFunctionPtrRef();
      else
        return m_Functions[m_FunctionNum - 1];
    }
  public:
    INT			GetFunctionNum(void)const{ return m_FunctionNum; }
    Function*	GetFunction(INT index)const
    {
      if (NULL == m_Functions || index < 0 || index >= m_FunctionNum || index >= m_MaxFunctionNum)
        return 0;
      return m_Functions[index];
    }
  public:
    Statement(DslFile& dataFile);
    virtual ~Statement(void)
    {
      ReleaseFunctions();
    }
  private:
    void				  PrepareFunctions(void);
    void				  ReleaseFunctions(void);
  private:
    Function**	  m_Functions;
    INT					  m_FunctionNum;
    INT					  m_FunctionSpace;
    INT					  m_MaxFunctionNum;
  };

  class ErrorAndStringBuffer
  {
  public:
    void				    ClearErrorInfo(void);
    void				    AddError(const CHAR* error);
    BOOL			HasError(void)const{ return m_HasError; }
    INT			GetErrorNum(void)const{ return m_ErrorNum; }
    const CHAR*	GetErrorInfo(INT index) const
    {
      if (index < 0 || index >= m_ErrorNum || index >= MAX_RECORD_ERROR_NUM)
        return "";
      return m_ErrorInfo[index];
    }
    CHAR*		NewErrorInfo(void)
    {
      m_HasError = TRUE;
      if (m_ErrorNum < MAX_RECORD_ERROR_NUM) {
        ++m_ErrorNum;
        return m_ErrorInfo[m_ErrorNum - 1];
      } else {
        return 0;
      }
    }
  public:
    INT			GetUnusedStringLength(void)const
    {
      CrashAssert(m_pStringBuffer);
      CrashAssert(m_ppUnusedStringRef);
      return m_MaxStringBufferLength - INT(*m_ppUnusedStringRef - m_pStringBuffer);
    }
    CHAR*&		GetUnusedStringPtrRef(void)
    {
      CrashAssert(m_ppUnusedStringRef);
      return *m_ppUnusedStringRef;
    }
  public:
    ErrorAndStringBuffer(void) :m_pStringBuffer(NULL), m_ppUnusedStringRef(NULL), m_MaxStringBufferLength(0)
    {
      ClearErrorInfo();
    }
    void Reset(CHAR* pStringBuffer, CHAR*& pUnusedStringRef, INT maxStringBufferLength)
    {
      ClearErrorInfo();
      m_pStringBuffer = pStringBuffer;
      m_ppUnusedStringRef = &pUnusedStringRef;
      m_MaxStringBufferLength = maxStringBufferLength;
      CrashAssert(m_pStringBuffer);
      CrashAssert(m_ppUnusedStringRef);
    }
  private:
    BOOL	m_HasError;
    CHAR	m_ErrorInfo[MAX_RECORD_ERROR_NUM][MAX_ERROR_INFO_CAPACITY];
    INT		m_ErrorNum;
    CHAR*	m_pStringBuffer;
    CHAR**	m_ppUnusedStringRef;
    INT		m_MaxStringBufferLength;
  };

  class DslFile
  {
    typedef ISyntaxComponent* SyntaxComponentPtr;
    typedef Statement* StatementPtr;
  public:
    INT		        GetDslInfoNum(void)const{ return m_DslInfoNum; }
    Statement*    GetDslInfo(INT index)const
    {
      if (index < 0 || index >= m_DslInfoNum)
        return NULL;
      return m_DslInfos[index];
    }
    void          WriteToFile(FILE* fp, int indent) const;
  public:
    void				  AddStatement(Statement* p);
    Value*        AddNewValueComponent(void);
    Call*         AddNewCallComponent(void);
    Function*			AddNewFunctionComponent(void);
    Statement*		AddNewStatementComponent(void);
  private:
    void          AddSyntaxComponent(ISyntaxComponent* p);
  private:
    SyntaxComponentPtr* m_SyntaxComponentPool;
    int           m_SyntaxComponentNum;
  public:
    CHAR*				  AllocString(INT len);
    CHAR*				  AllocString(const CHAR* src);
    CHAR*	        GetStringBuffer(void)const{ return m_StringBuffer; }
    CHAR*&	      GetUnusedStringPtrRef(void){ return m_UnusedStringPtr; }
  public:
    DslFile(void);
    DslFile(const ParserOptions& options);
    ~DslFile(void);
    void				  Reset(void);
  private:
    void				  Init(void);
    void				  Release(void);
  private:
    CHAR*				  m_StringBuffer;
    CHAR*				  m_UnusedStringPtr;
    StatementPtr*	m_DslInfos;
    INT					  m_DslInfoNum;
  public:
    void		      EnableDebugInfo(void){ m_IsDebugInfoEnable = TRUE; }
    void		      DisableDebugInfo(void){ m_IsDebugInfoEnable = FALSE; }
    BOOL		      IsDebugInfoEnable(void)const{ return m_IsDebugInfoEnable; }
  private:
    BOOL				  m_IsDebugInfoEnable;
  public:
    void		      ClearErrorInfo(void){ m_ErrorAndStringBuffer.ClearErrorInfo(); }
    void		      AddError(const CHAR* error){ m_ErrorAndStringBuffer.AddError(error); }
    BOOL		      HasError(void)const{ return m_ErrorAndStringBuffer.HasError(); }
    INT		        GetErrorNum(void){ return m_ErrorAndStringBuffer.GetErrorNum(); }
    const CHAR*	  GetErrorInfo(INT index) const{ return m_ErrorAndStringBuffer.GetErrorInfo(index); }
    CHAR*	        NewErrorInfo(void){ return m_ErrorAndStringBuffer.NewErrorInfo(); }
  public:
    ErrorAndStringBuffer&		    GetErrorAndStringBuffer(void){ return m_ErrorAndStringBuffer; }
    const ErrorAndStringBuffer&	GetErrorAndStringBuffer(void)const{ return m_ErrorAndStringBuffer; }
  private:
    ErrorAndStringBuffer        m_ErrorAndStringBuffer;
  public:
    ParserOptions&			        GetOptions(void){ return m_Options; }
    const ParserOptions&	      GetOptions(void)const{ return m_Options; }
  private:
    ParserOptions	              m_Options;
  };

  class IScriptSource
  {
  public:
    virtual ~IScriptSource(void){}
  public:
    class Iterator
    {
    public:
      const CHAR& operator * (void) const
      {
        return Peek(0);
      }
      Iterator& operator ++ (void)
      {
        Advance();
        return *this;
      }
      const Iterator operator ++ (INT)
      {
        Iterator it = *this;
        ++(*this);
        return it;
      }
      const Iterator operator + (INT val) const
      {
        Iterator it = *this;
        for (INT ix = 0; ix < val; ++ix)
          it.Advance();
        return it;
      }
      BOOL Load(void)
      {
        if (NULL != m_pSource) {
          BOOL r = m_pSource->Load();
          if (r) {
            *this = m_pSource->GetIterator();
          }
          return r;
        } else {
          return FALSE;
        }
      }
      const CHAR* GetBuffer(void)const
      {
        return m_pSource->GetBuffer();
      }
      const CHAR* GetLeft(void)const
      {
        return m_Iterator;
      }
    public:
      BOOL operator ==(const Iterator& other) const
      {
        return m_pSource == other.m_pSource && m_Iterator == other.m_Iterator && m_EndIterator == other.m_EndIterator;
      }
      BOOL operator !=(const Iterator& other) const
      {
        return !(operator ==(other));
      }
    public:
      Iterator(void) :m_pSource(NULL), m_Iterator(""), m_EndIterator(m_Iterator)
      {}
      explicit Iterator(IScriptSource& source) :m_pSource(&source)
      {
        const CHAR* p = m_pSource->GetBuffer();
        if (0 == p) {
          m_Iterator = "";
          m_EndIterator = m_Iterator;
        } else {
          m_Iterator = p;
          m_EndIterator = m_Iterator + strlen(p);
        }
      }
      Iterator(const Iterator& other)
      {
        CopyFrom(other);
      }
      Iterator& operator=(const Iterator& other)
      {
        if (this == &other)
          return *this;
        CopyFrom(other);
        return *this;
      }
    private:
      const CHAR& Peek(INT index)const
      {
        if (m_Iterator + index < m_EndIterator)
          return *(m_Iterator + index);
        else
          return *m_EndIterator;
      }
      void Advance(void)
      {
        if (m_Iterator < m_EndIterator)
          ++m_Iterator;
      }
      void CopyFrom(const Iterator& other)
      {
        m_pSource = other.m_pSource;
        m_Iterator = other.m_Iterator;
        m_EndIterator = other.m_EndIterator;
      }
    private:
      IScriptSource* m_pSource;
      const CHAR* m_Iterator;
      const CHAR* m_EndIterator;
    };
    friend class Iterator;
  public:
    Iterator GetIterator(void)
    {
      return Iterator(*this);
    }
  protected:
    virtual BOOL Load(void) = 0;
    virtual const CHAR* GetBuffer(void)const = 0;
  };
}
using namespace Dsl;

#endif
