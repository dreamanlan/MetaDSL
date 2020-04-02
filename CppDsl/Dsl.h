/*****************************************************************************

calc.h

******************************************************************************/

#ifndef _CALC_H
#define _CALC_H

#include "BaseType.h"

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
		DELTA_COMMENT = 2,
	};

	enum
	{
		MAX_FUNCTION_DIMENSION_NUM = 8,
		MAX_STATEMENT_NUM = 1024,
		MAX_PROGRAM_SIZE = 16 * 1024,
		STRING_BUFFER_SIZE = 1024 * 1024,
		SYNTAXCOMPONENT_POOL_SIZE = 16 * 1024,
	};

	class DslOptions
	{
	public:
		DslOptions(void) :
			m_MaxFunctionDimensionNum(MAX_FUNCTION_DIMENSION_NUM),
			m_MaxStatementNum(MAX_STATEMENT_NUM),
			m_MaxProgramSize(MAX_PROGRAM_SIZE),
			m_StringBufferSize(STRING_BUFFER_SIZE),
			m_SyntaxComponentPoolSize(SYNTAXCOMPONENT_POOL_SIZE)
		{
		}
	public:
		int GetMaxFunctionDimensionNum() const { return m_MaxFunctionDimensionNum; }
		void SetMaxFunctionDimensionNum(int val) { m_MaxFunctionDimensionNum = val; }
		int GetMaxStatementNum() const { return m_MaxStatementNum; }
		void SetMaxStatementNum(int val) { m_MaxStatementNum = val; }
		int GetMaxProgramSize() const { return m_MaxProgramSize; }
		void SetMaxProgramSize(int val) { m_MaxProgramSize = val; }
		int GetStringBufferSize() const { return m_StringBufferSize; }
		void SetStringBufferSize(int val) { m_StringBufferSize = val; }
		int GetSyntaxComponentPoolSize(void) const { return m_SyntaxComponentPoolSize; }
		void SetSyntaxComponentPoolSize(int val) { m_SyntaxComponentPoolSize = val; }
	private:
		int	m_MaxFunctionDimensionNum;
		int	m_MaxStatementNum;
		int	m_MaxProgramSize;
		int	m_StringBufferSize;
		int m_SyntaxComponentPoolSize;
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
		ISyntaxComponent(int syntaxType);
		virtual ~ISyntaxComponent(void);
	public:
		virtual int IsValid(void) const = 0;
		virtual const char* GetId(void) const = 0;
		virtual int GetIdType(void) const = 0;
		virtual int GetLine(void) const = 0;
		virtual void WriteToFile(FILE* fp, int indent, int firstLineNoIndent, int isLastOfStatement) const = 0;
	public:
		int GetSyntaxType(void) const { return m_SyntaxType; }
		void AddFirstComment(const char* cmt)
		{
			PrepareFirstComments();
			if (m_FirstCommentNum < m_FirstCommentSpace) {
				m_FirstComments[m_FirstCommentNum++] = cmt;
			}
		}
		void RemoveFirstComment(int index)
		{
			if (index >= 0 && index < m_FirstCommentNum) {
				for (int ix = index; ix < m_FirstCommentNum - 1; ++ix) {
					m_FirstComments[ix] = m_FirstComments[ix + 1];
				}
				--m_FirstCommentNum;
			}
		}
		void ClearFirstComments()
		{
			m_FirstCommentNum = 0;
		}
		int GetFirstCommentNum(void) const { return m_FirstCommentNum; }
		const char* GetFirstComment(int index) const
		{
			if (index >= 0 && index < m_FirstCommentNum) {
				return m_FirstComments[index];
			}
			else {
				return 0;
			}
		}
		int IsFirstCommentOnNewLine(void) const { return m_FirstCommentOnNewLine; }
		void SetFirstCommentOnNewLine(int v) { m_FirstCommentOnNewLine = v; }
		void AddLastComment(const char* cmt)
		{
			PrepareLastComments();
			if (m_LastCommentNum < m_LastCommentSpace) {
				m_LastComments[m_LastCommentNum++] = cmt;
			}
		}
		void RemoveLastComment(int index)
		{
			if (index >= 0 && index < m_LastCommentNum) {
				for (int ix = index; ix < m_LastCommentNum - 1; ++ix) {
					m_LastComments[ix] = m_LastComments[ix + 1];
				}
				--m_LastCommentNum;
			}
		}
		void ClearLastComments()
		{
			m_LastCommentNum = 0;
		}
		int GetLastCommentNum(void) const { return m_LastCommentNum; }
		const char* GetLastComment(int index) const
		{
			if (index >= 0 && index < m_LastCommentNum) {
				return m_LastComments[index];
			}
			else {
				return 0;
			}
		}
		int IsLastCommentOnNewLine(void) const { return m_LastCommentOnNewLine; }
		void SetLastCommentOnNewLine(int v) { m_LastCommentOnNewLine = v; }
		void CopyComments(const ISyntaxComponent& other)
		{
			CopyFirstComments(other);
			CopyLastComments(other);
		}
		void CopyFirstComments(const ISyntaxComponent& other)
		{
			int fnum = other.GetFirstCommentNum();
			if (fnum > 0) {
				m_FirstCommentOnNewLine = other.m_FirstCommentOnNewLine;
				for (int i = 0; i < fnum; ++i) {
					AddFirstComment(other.GetFirstComment(i));
				}
			}
		}
		void CopyLastComments(const ISyntaxComponent& other)
		{
			int lnum = other.GetLastCommentNum();
			if (lnum > 0) {
				m_LastCommentOnNewLine = other.m_LastCommentOnNewLine;
				for (int i = 0; i < lnum; ++i) {
					AddLastComment(other.GetLastComment(i));
				}
			}
		}
	protected:
		void CopyFrom(const ISyntaxComponent& other);
		void WriteFirstCommentsToFile(FILE* fp, int indent, int firstLineNoIndent) const;
		void WriteLastCommentsToFile(FILE* fp, int indent, int isLastOfStatement) const;
	private:
		void PrepareFirstComments(void);
		void ReleaseFirstComments(void);
		void PrepareLastComments(void);
		void ReleaseLastComments(void);
	private:
		int						  m_SyntaxType;
		const char**              m_FirstComments;
		int                       m_FirstCommentNum;
		int                       m_FirstCommentSpace;
		int                       m_FirstCommentOnNewLine;
		const char**              m_LastComments;
		int                       m_LastCommentNum;
		int                       m_LastCommentSpace;
		int                       m_LastCommentOnNewLine;
	};

	class Call;
	class Value : public ISyntaxComponent
	{
	public:
		enum
		{
			TYPE_INVALID = -1,
			TYPE_IDENTIFIER = 0,
			TYPE_NUM,
			TYPE_STRING,
			TYPE_BOOL,
			TYPE_CALL,
		};

		Value(void) :ISyntaxComponent(ISyntaxComponent::TYPE_VALUE), m_Type(TYPE_INVALID), m_StringVal(0), m_Line(0) {}
		explicit Value(char* val) :ISyntaxComponent(ISyntaxComponent::TYPE_VALUE), m_Type(TYPE_STRING), m_StringVal(val), m_Line(0) {}
		explicit Value(const char* val) :ISyntaxComponent(ISyntaxComponent::TYPE_VALUE), m_Type(TYPE_STRING), m_ConstStringVal(val), m_Line(0) {}
		explicit Value(Call* val) :ISyntaxComponent(ISyntaxComponent::TYPE_VALUE), m_Type(TYPE_CALL), m_Call(val), m_Line(0) {}
		explicit Value(char* val, int type) :ISyntaxComponent(ISyntaxComponent::TYPE_VALUE), m_Type(type), m_StringVal(val), m_Line(0) {}
		explicit Value(const char* val, int type) :ISyntaxComponent(ISyntaxComponent::TYPE_VALUE), m_Type(type), m_ConstStringVal(val), m_Line(0) {}
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

		virtual int IsValid(void)const { return (m_Type != TYPE_INVALID ? TRUE : FALSE); }
		virtual int GetIdType(void)const { return m_Type; }
		virtual const char* GetId(void)const { return m_StringVal; }
		virtual int GetLine(void)const { return m_Line; }
		virtual void WriteToFile(FILE* fp, int indent, int firstLineNoIndent, int isLastOfStatement) const;

		Call* GetCall(void)const { return m_Call; }

		bool HaveId()const { return IsValid(); }
		int IsNum(void)const { return (m_Type == TYPE_NUM ? TRUE : FALSE); }
		int IsString(void)const { return (m_Type == TYPE_STRING ? TRUE : FALSE); }
		int IsVariableName(void)const { return (m_Type == TYPE_IDENTIFIER ? TRUE : FALSE); }
		int IsCall(void)const { return (m_Type == TYPE_CALL ? TRUE : FALSE); }

		void SetInvalid(void)
		{
			m_Type = TYPE_INVALID;
			m_StringVal = 0;
		}
		void SetNumber(char* str)
		{
			m_Type = TYPE_NUM;
			m_StringVal = str;
		}
		void SetNumber(const char* str)
		{
			m_Type = TYPE_NUM;
			m_ConstStringVal = str;
		}
		void SetString(char* str)
		{
			m_Type = TYPE_STRING;
			m_StringVal = str;
		}
		void SetString(const char* str)
		{
			m_Type = TYPE_STRING;
			m_ConstStringVal = str;
		}
		void SetBool(char* str)
		{
			m_Type = TYPE_BOOL;
			m_StringVal = str;
		}
		void SetBool(const char* str)
		{
			m_Type = TYPE_BOOL;
			m_ConstStringVal = str;
		}
		void SetCall(Call* func)
		{
			m_Type = TYPE_CALL;
			m_Call = func;
		}
		void SetVariableName(char* name)
		{
			m_Type = TYPE_IDENTIFIER;
			m_StringVal = name;
		}
		void SetLine(int line)
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
		int					m_Type;
		union
		{
			char*				m_StringVal;
			const char*		m_ConstStringVal;//在脚本里与m_StringVal类型相同,用于实现自动const_cast
			Call*				m_Call;
		};
		int					m_Line;
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
		NullSyntax(void) : ISyntaxComponent(ISyntaxComponent::TYPE_NULL) {}
	public:
		virtual int IsValid(void) const { return FALSE; }
		virtual const char* GetId(void) const { return ""; }
		virtual int GetIdType(void) const { return Value::TYPE_INVALID; }
		virtual int GetLine(void) const { return 0; }
		virtual void WriteToFile(FILE* fp, int indent, int firstLineNoIndent, int isLastOfStatement) const {}
	private:
		NullSyntax(const NullSyntax&);
		NullSyntax& operator=(const NullSyntax&);
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
			PARAM_CLASS_QUESTION_PERIOD,
			PARAM_CLASS_QUESTION_PARENTHESIS,
			PARAM_CLASS_QUESTION_BRACKET,
			PARAM_CLASS_QUESTION_BRACE,
			PARAM_CLASS_POINTER,
			PARAM_CLASS_PERIOD_STAR,
			PARAM_CLASS_QUESTION_PERIOD_STAR,
			PARAM_CLASS_POINTER_STAR,
			PARAM_CLASS_OPERATOR,
			PARAM_CLASS_TERNARY_OPERATOR,
            PARAM_CLASS_MAX,
            PARAM_CLASS_WRAP_INFIX_CALL_MASK = 0x40,
            PARAM_CLASS_UNMASK = 0x3F,
		};
		typedef ISyntaxComponent* SyntaxComponentPtr;
	public:
		virtual int IsValid(void)const
		{
			if (HaveId())
				return TRUE;
			else if (HaveParam())
				return TRUE;
			else
				return FALSE;
		}
		virtual int GetIdType(void)const { return m_Name.GetIdType(); }
		virtual const char* GetId(void)const { return m_Name.GetId(); }
		virtual int GetLine(void)const { return m_Name.GetLine(); }
		virtual void WriteToFile(FILE* fp, int indent, int firstLineNoIndent, int isLastOfStatement) const;
	public:
		void		SetName(const Value& val) { m_Name = val; }
		Value&		GetName(void) { return m_Name; }
		void		ClearParams(void) { m_ParamNum = 0; }
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
		void		SetParam(int index, ISyntaxComponent* pVal)
		{
			if (NULL == pVal || index < 0 || index >= MAX_FUNCTION_PARAM_NUM)
				return;
			m_Params[index] = pVal;
		}
		void		SetParamClass(int v) { m_ParamClass = v; }
		int			GetParamClass(void)const { return m_ParamClass; }
		int			HaveId(void)const { return m_Name.HaveId(); }
		int			HaveParam(void)const { return m_ParamClass != PARAM_CLASS_NOTHING; }
		int			IsHighOrder(void)const { return m_Name.IsCall(); }
	public:
		const Value&		GetName(void)const { return m_Name; }
		int					GetParamNum(void)const { return m_ParamNum; }
		ISyntaxComponent*	GetParam(int index)const
		{
			if (0 == m_Params || index < 0 || index >= m_ParamNum || index >= MAX_FUNCTION_PARAM_NUM)
				return 0;
			return m_Params[index];
		}
		const char*			GetParamId(int index)const
		{
			if (0 == m_Params || index < 0 || index >= m_ParamNum || index >= MAX_FUNCTION_PARAM_NUM)
				return 0;
			return m_Params[index]->GetId();
		}
	public:
		void AddComment(const char* cmt)
		{
			PrepareComments();
			if (m_CommentNum < m_CommentSpace) {
				m_Comments[m_CommentNum++] = cmt;
			}
		}
		void RemoveComment(int index)
		{
			if (index >= 0 && index < m_CommentNum) {
				for (int ix = index; ix < m_CommentNum - 1; ++ix) {
					m_Comments[ix] = m_Comments[ix + 1];
				}
				--m_CommentNum;
			}
		}
		void ClearComments()
		{
			m_CommentNum = 0;
		}
		int GetCommentNum(void) const { return m_CommentNum; }
		const char* GetComment(int index) const
		{
			if (index >= 0 && index < m_CommentNum) {
				return m_Comments[index];
			}
			else {
				return 0;
			}
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
		void          PrepareComments(void);
		void          ReleaseComments(void);
	private:
		Value			          m_Name;
		ISyntaxComponent**	m_Params;
		int				          m_ParamNum;
		int				          m_ParamSpace;
		int				          m_ParamClass;
		const char**        m_Comments;
		int                 m_CommentNum;
		int                 m_CommentSpace;
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
            EXTENT_CLASS_MAX,
		};
		typedef ISyntaxComponent* SyntaxComponentPtr;
	public:
		virtual int IsValid(void)const
		{
			if (m_Call.IsValid())
				return TRUE;
			else if (HaveStatement() || HaveExternScript())
				return TRUE;
			else
				return FALSE;
		}
		virtual int GetIdType(void)const { return m_Call.GetIdType(); }
		virtual const char* GetId(void)const { return m_Call.GetId(); }
		virtual int GetLine(void)const { return m_Call.GetLine(); }
		virtual void WriteToFile(FILE* fp, int indent, int firstLineNoIndent, int isLastOfStatement) const;
	public:
		void		SetCall(const Call& val) { m_Call = val; }
		Call&		GetCall(void) { return m_Call; }
		void		ClearStatements(void) { m_StatementNum = 0; }
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
		void		SetStatement(int index, ISyntaxComponent* pVal)
		{
			if (NULL == pVal || index < 0 || index >= m_MaxStatementNum)
				return;
			m_Statements[index] = pVal;
		}
		void		SetExternScript(const char* scp) { m_ExternScript = scp; }
		void		SetExtentClass(int v) { m_ExtentClass = v; }
		int			GetExtentClass(void)const { return m_ExtentClass; }
		int			HaveId(void)const { return m_Call.HaveId(); }
		int			HaveParam(void)const { return m_Call.HaveParam(); }
		int			HaveStatement(void)const { return m_ExtentClass == EXTENT_CLASS_STATEMENT; }
		int			HaveExternScript(void)const { return m_ExtentClass == EXTENT_CLASS_EXTERN_SCRIPT; }
	public:
		const Call&	GetCall(void)const { return m_Call; }
		int			    GetStatementNum(void)const { return m_StatementNum; }
		ISyntaxComponent*	GetStatement(int index)const
		{
			if (0 == m_Statements || index < 0 || index >= m_StatementNum || index >= m_MaxStatementNum)
				return 0;
			return m_Statements[index];
		}
		const char*	GetExternScript(void)const { return m_ExternScript; }
	public:
		Function(DslFile& dataFile);
		virtual ~Function(void);
	private:
		Function(const Function&);
		Function& operator=(const Function&);
	private:
		void          PrepareStatements(void);
		void          ReleaseStatements(void);
	private:
		Call			          m_Call;
		ISyntaxComponent**  m_Statements;
		int				          m_StatementNum;
		int				          m_StatementSpace;
		int				          m_MaxStatementNum;
		const char*		      m_ExternScript;
		int				          m_ExtentClass;
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
		virtual int IsValid(void)const
		{
			if (NULL != m_Functions && m_FunctionNum > 0 && m_Functions[0]->IsValid())
				return TRUE;
			else
				return FALSE;
		}
		virtual int GetIdType(void)const
		{
			int type = Value::TYPE_INVALID;
			if (IsValid()) {
				type = m_Functions[0]->GetIdType();
			}
			return type;
		}
		virtual const char* GetId(void)const
		{
			const char* str = "";
			if (IsValid()) {
				str = m_Functions[0]->GetId();
			}
			return str;
		}
		virtual int GetLine(void)const
		{
			int line = 0;
			if (IsValid()) {
				line = m_Functions[0]->GetLine();
			}
			return line;
		}
		virtual void WriteToFile(FILE* fp, int indent, int firstLineNoIndent, int isLastOfStatement) const;
	public:
		void		ClearFunctions(void) { m_FunctionNum = 0; }
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
		int			GetFunctionNum(void)const { return m_FunctionNum; }
		Function*	GetFunction(int index)const
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
		Statement(const Statement&);
		Statement& operator=(const Statement&);
	private:
		void				  PrepareFunctions(void);
		void				  ReleaseFunctions(void);
	private:
		Function**	  m_Functions;
		int					  m_FunctionNum;
		int					  m_FunctionSpace;
		int					  m_MaxFunctionNum;
	};

	class ErrorAndStringBuffer
	{
	public:
		void				    ClearErrorInfo(void);
		void				    AddError(const char* error);
		int			HasError(void)const { return m_HasError; }
		int			GetErrorNum(void)const { return m_ErrorNum; }
		const char*	GetErrorInfo(int index) const
		{
			if (index < 0 || index >= m_ErrorNum || index >= MAX_RECORD_ERROR_NUM)
				return "";
			return m_ErrorInfo[index];
		}
		char*		NewErrorInfo(void)
		{
			m_HasError = TRUE;
			if (m_ErrorNum < MAX_RECORD_ERROR_NUM) {
				++m_ErrorNum;
				return m_ErrorInfo[m_ErrorNum - 1];
			}
			else {
				return 0;
			}
		}
	public:
		int			GetUnusedStringLength(void)const
		{
			MyAssert(m_pStringBuffer);
			MyAssert(m_ppUnusedStringRef);
			return m_MaxStringBufferLength - int(*m_ppUnusedStringRef - m_pStringBuffer);
		}
		char*&		GetUnusedStringPtrRef(void)
		{
			MyAssert(m_ppUnusedStringRef);
			return *m_ppUnusedStringRef;
		}
	public:
		ErrorAndStringBuffer(void) :m_pStringBuffer(NULL), m_ppUnusedStringRef(NULL), m_MaxStringBufferLength(0)
		{
			ClearErrorInfo();
		}
		void Reset(char* pStringBuffer, char*& pUnusedStringRef, int maxStringBufferLength)
		{
			ClearErrorInfo();
			m_pStringBuffer = pStringBuffer;
			m_ppUnusedStringRef = &pUnusedStringRef;
			m_MaxStringBufferLength = maxStringBufferLength;
			MyAssert(m_pStringBuffer);
			MyAssert(m_ppUnusedStringRef);
		}
	private:
		ErrorAndStringBuffer(const ErrorAndStringBuffer&);
		ErrorAndStringBuffer& operator=(const ErrorAndStringBuffer&);
	private:
		int	m_HasError;
		char	m_ErrorInfo[MAX_RECORD_ERROR_NUM][MAX_ERROR_INFO_CAPACITY];
		int		m_ErrorNum;
		char*	m_pStringBuffer;
		char**	m_ppUnusedStringRef;
		int		m_MaxStringBufferLength;
	};

	class IScriptSource;
	class DslFile
	{
		typedef ISyntaxComponent* SyntaxComponentPtr;
		typedef Statement* StatementPtr;
	public:
		int		        GetDslInfoNum(void)const { return m_DslInfoNum; }
		Statement*    GetDslInfo(int index)const
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
		char*				  AllocString(int len);
		char*				  AllocString(const char* src);
		char*	        GetStringBuffer(void)const { return m_StringBuffer; }
		char*&	      GetUnusedStringPtrRef(void) { return m_UnusedStringPtr; }
	public:
		DslFile(void);
		DslFile(const DslOptions& options);
		~DslFile(void);
		void				  Reset(void);
		void          Parse(const char* buf);
		void          Parse(IScriptSource& source);
	private:
		DslFile(const DslFile&);
		DslFile& operator=(const DslFile&);
	private:
		void				  Init(void);
		void				  Release(void);
	private:
		char*				  m_StringBuffer;
		char*				  m_UnusedStringPtr;
		StatementPtr*	m_DslInfos;
		int					  m_DslInfoNum;
	public:
		void		      EnableDebugInfo(void) { m_IsDebugInfoEnable = TRUE; }
		void		      DisableDebugInfo(void) { m_IsDebugInfoEnable = FALSE; }
		int		        IsDebugInfoEnable(void)const { return m_IsDebugInfoEnable; }
	private:
		int				    m_IsDebugInfoEnable;
	public:
		void		      ClearErrorInfo(void) { m_ErrorAndStringBuffer.ClearErrorInfo(); }
		void		      AddError(const char* error) { m_ErrorAndStringBuffer.AddError(error); }
		int		        HasError(void)const { return m_ErrorAndStringBuffer.HasError(); }
		int		        GetErrorNum(void) { return m_ErrorAndStringBuffer.GetErrorNum(); }
		const char*	  GetErrorInfo(int index) const { return m_ErrorAndStringBuffer.GetErrorInfo(index); }
		char*	        NewErrorInfo(void) { return m_ErrorAndStringBuffer.NewErrorInfo(); }
	public:
		ErrorAndStringBuffer&		    GetErrorAndStringBuffer(void) { return m_ErrorAndStringBuffer; }
		const ErrorAndStringBuffer&	GetErrorAndStringBuffer(void)const { return m_ErrorAndStringBuffer; }
	private:
		ErrorAndStringBuffer        m_ErrorAndStringBuffer;
	public:
		DslOptions&			        GetOptions(void) { return m_Options; }
		const DslOptions&	      GetOptions(void)const { return m_Options; }
	private:
		DslOptions	              m_Options;
	};

	class IScriptSource
	{
	public:
		virtual ~IScriptSource(void) {}
	public:
		class Iterator
		{
		public:
			const char& operator * (void) const
			{
				return Peek(0);
			}
			Iterator& operator ++ (void)
			{
				Advance();
				return *this;
			}
			const Iterator operator ++ (int)
			{
				Iterator it = *this;
				++(*this);
				return it;
			}
			const Iterator operator + (int val) const
			{
				Iterator it = *this;
				for (int ix = 0; ix < val; ++ix)
					it.Advance();
				return it;
			}
			int Load(void)
			{
				if (NULL != m_pSource) {
					int r = m_pSource->Load();
					if (r) {
						*this = m_pSource->GetIterator();
					}
					return r;
				}
				else {
					return FALSE;
				}
			}
			const char* GetBuffer(void)const
			{
				return m_pSource->GetBuffer();
			}
			const char* GetLeft(void)const
			{
				return m_Iterator;
			}
		public:
			int operator ==(const Iterator& other) const
			{
				return m_pSource == other.m_pSource && m_Iterator == other.m_Iterator && m_EndIterator == other.m_EndIterator;
			}
			int operator !=(const Iterator& other) const
			{
				return !(operator ==(other));
			}
		public:
			Iterator(void) :m_pSource(NULL), m_Iterator(""), m_EndIterator(m_Iterator)
			{
			}
			explicit Iterator(IScriptSource& source) :m_pSource(&source)
			{
				const char* p = m_pSource->GetBuffer();
				if (0 == p) {
					m_Iterator = "";
					m_EndIterator = m_Iterator;
				}
				else {
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
			const char& Peek(int index)const
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
			const char* m_Iterator;
			const char* m_EndIterator;
		};
		friend class Iterator;
	public:
		Iterator GetIterator(void)
		{
			return Iterator(*this);
		}
	protected:
		virtual int Load(void) = 0;
		virtual const char* GetBuffer(void)const = 0;
	};
}
using namespace Dsl;

#endif
