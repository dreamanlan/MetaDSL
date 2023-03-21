using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Runtime.CompilerServices;
using System.Text;

namespace Dsl
{
    public delegate void DslLogDelegation(string msg);
    internal enum DslBinaryCode
    {
        BeginStatement = 1,
        EndStatement,
        EndStatementWithComma,
        EndStatementWithSemiColon,
        BeginFunction,
        EndFunction,
        EndFunctionWithComma,
        EndFunctionWithSemiColon,
        BeginValue,
        EndValue,
        EndValueWithComma,
        EndValueWithSemiColon,
        ValueTypeBegin,
        ValueTypeEnd = ValueTypeBegin + ValueData.MAX_TYPE,
        ParamOrExternClassBegin
    }

    internal class SyntaxComponentCommentsInfo
    {
        internal List<string> mFirstComments = null;
        internal bool mFirstCommentOnNewLine = false;
        internal List<string> mLastComments = null;
        internal bool mLastCommentOnNewLine = false;
    }
    internal class FunctionCommentsInfo : SyntaxComponentCommentsInfo
    {
        internal List<string> m_Comments = null;
    }
    /// <summary>
    /// 基于函数样式的脚本化数据解析工具。可以用作DSL元语言。
    /// </summary>
    /// <remarks>
    /// 混淆的当前实现要求脚本里不能出现`字符。另外，测试代码的加解密表的设计要求脚本里不能出现以形如“_数字_”的标识符。
    /// </remarks>
    public interface ISyntaxComponent
    {
        bool IsValid();
        string GetId();
        int GetIdType();
        int GetLine();
        string ToScriptString(bool includeComment);
        bool HaveId();

        void SetSeparator(int sep);
        int GetSeparator();
        char GetSepChar();

        string CalcFirstComment();
        string CalcLastComment();
        void CopyComments(ISyntaxComponent other);
        void CopyFirstComments(ISyntaxComponent other);
        void CopyLastComments(ISyntaxComponent other);
        List<string> FirstComments { get; }
        bool FirstCommentOnNewLine { get; set; }
        List<string> LastComments { get; }
        bool LastCommentOnNewLine { get; set; }
    }

    public abstract class AbstractSyntaxComponent : ISyntaxComponent
    {
        public const int ID_TOKEN = 0;
        public const int NUM_TOKEN = 1;
        public const int STRING_TOKEN = 2;
        public const int MAX_TYPE = 2;

        public const int SEPARATOR_NOTHING = 0;
        public const int SEPARATOR_COMMA = 1;
        public const int SEPARATOR_SEMICOLON = 2;

        public abstract bool IsValid();
        public abstract string GetId();
        public abstract int GetIdType();
        public abstract int GetLine();
        public abstract string ToScriptString(bool includeComment);
        public abstract bool HaveId();

        public void SetSeparator(int sep)
        {
            m_Separator = sep;
        }
        public int GetSeparator()
        {
            return m_Separator;
        }
        public char GetSepChar()
        {
            switch(m_Separator) {
                case SEPARATOR_COMMA:
                    return ',';
                case SEPARATOR_SEMICOLON:
                    return ';';
                default:
                    return ' ';
            }
        }

        public string CalcFirstComment()
        {
            if (DslFile.DontLoadComments)
                return string.Empty;
            var cmtsInfo = GetCommentsInfo();
            if (null == cmtsInfo || null == cmtsInfo.mFirstComments) {
                return string.Empty;
            }
            else {
                return string.Join(string.Empty, cmtsInfo.mFirstComments.ToArray());
            }
        }
        public string CalcLastComment()
        {
            if (DslFile.DontLoadComments)
                return string.Empty;
            var cmtsInfo = GetCommentsInfo();
            if (null == cmtsInfo || null == cmtsInfo.mLastComments) {
                return string.Empty;
            }
            else {
                return string.Join(string.Empty, cmtsInfo.mLastComments.ToArray());
            }
        }
        public void CopyComments(ISyntaxComponent other)
        {
            CopyFirstComments(other);
            CopyLastComments(other);
        }
        public void CopyFirstComments(ISyntaxComponent other)
        {
            if (DslFile.DontLoadComments)
                return;
            if (other.FirstComments.Count > 0) {
                FirstComments.AddRange(other.FirstComments);
                FirstCommentOnNewLine = other.FirstCommentOnNewLine;
            }
        }
        public void CopyLastComments(ISyntaxComponent other)
        {
            if (DslFile.DontLoadComments)
                return;
            if (other.LastComments.Count > 0) {
                LastComments.AddRange(other.LastComments);
                LastCommentOnNewLine = other.LastCommentOnNewLine;
            }
        }

        public List<string> FirstComments
        {
            get {
                if (DslFile.DontLoadComments)
                    return NullSyntax.EmptyStringList;
                var cmtsInfo = GetCommentsInfo();
                if (null == cmtsInfo)
                    return NullSyntax.EmptyStringList;
                if (null == cmtsInfo.mFirstComments) {
                    cmtsInfo.mFirstComments = new List<string>();
                }
                return cmtsInfo.mFirstComments;
            }
        }
        public bool FirstCommentOnNewLine
        {
            get {
                if (DslFile.DontLoadComments)
                    return false;
                var cmtsInfo = GetCommentsInfo();
                if (null == cmtsInfo)
                    return false;
                return cmtsInfo.mFirstCommentOnNewLine;
            }
            set {
                if (DslFile.DontLoadComments)
                    return;
                var cmtsInfo = GetCommentsInfo();
                if (null == cmtsInfo)
                    return;
                cmtsInfo.mFirstCommentOnNewLine = value;
            }
        }
        public List<string> LastComments
        {
            get {
                if (DslFile.DontLoadComments)
                    return NullSyntax.EmptyStringList;
                var cmtsInfo = GetCommentsInfo();
                if (null == cmtsInfo)
                    return NullSyntax.EmptyStringList;
                if (null == cmtsInfo.mLastComments) {
                    cmtsInfo.mLastComments = new List<string>();
                }
                return cmtsInfo.mLastComments;
            }
        }
        public bool LastCommentOnNewLine
        {
            get {
                if (DslFile.DontLoadComments)
                    return false;
                var cmtsInfo = GetCommentsInfo();
                if (null == cmtsInfo)
                    return false;
                return cmtsInfo.mLastCommentOnNewLine;
            }
            set {
                if (DslFile.DontLoadComments)
                    return;
                var cmtsInfo = GetCommentsInfo();
                if (null == cmtsInfo)
                    return;
                cmtsInfo.mLastCommentOnNewLine = value;
            }
        }

        internal virtual SyntaxComponentCommentsInfo GetCommentsInfo()
        {
            return null;
        }

        private int m_Separator = AbstractSyntaxComponent.SEPARATOR_NOTHING;
    }
    public abstract class ValueOrFunctionData : AbstractSyntaxComponent
    {
        public bool IsValue
        {
            get { return this is ValueData; }
        }
        public bool IsFunction
        {
            get { return this is FunctionData; }
        }
        public ValueData AsValue
        {
            get { return this as ValueData; }
        }
        public FunctionData AsFunction
        {
            get { return this as FunctionData; }
        }
    }
    /// <summary>
    /// 空语法单件
    /// </summary>
    public class NullSyntax : AbstractSyntaxComponent
    {
        public override bool IsValid()
        {
            return false;
        }
        public override string GetId()
        {
            return string.Empty;
        }
        public override int GetIdType()
        {
            return ID_TOKEN;
        }
        public override int GetLine()
        {
            return -1;
        }
        public override string ToScriptString(bool includeComment)
        {
            return ToString();
        }
        public override bool HaveId()
        {
            return false;
        }

        public static NullSyntax Instance
        {
            get {
                return s_Instance;
            }
        }
        public static List<string> EmptyStringList
        {
            get {
                s_StringList.Clear();
                return s_StringList;
            }
        }
        private static NullSyntax s_Instance = new NullSyntax();
        private static List<string> s_StringList = new List<string>();
    }
    /// <summary>
    /// 用于描述变量、常量与无参命令语句。可能会出现在函数调用参数表与函数语句列表中。
    /// </summary>
    public class ValueData : ValueOrFunctionData
    {
        public override bool IsValid()
        {
            return HaveId();
        }
        public override string GetId()
        {
            return m_Id;
        }
        public override int GetIdType()
        {
            return m_Type;
        }
        public override int GetLine()
        {
            return m_Line;
        }
        public override string ToScriptString(bool includeComment)
        {
#if FULL_VERSION
            if (includeComment) {
                return CalcFirstComment() + Utility.quoteStringWithStrDefDelim(m_Id, m_Type) + CalcLastComment();
            }
            else {
                return Utility.quoteStringWithStrDefDelim(m_Id, m_Type);
            }
#else
      return ToString();
#endif
        }
        public override bool HaveId()
        {
            return !string.IsNullOrEmpty(m_Id) || m_Type == STRING_TOKEN;
        }

        public void SetId(string id)
        {
            m_Id = id;
        }
        public void SetType(int _type)
        {
            m_Type = _type;
        }
        public void SetLine(int line)
        {
            m_Line = line;
        }
        public bool IsId()
        {
            return ID_TOKEN == m_Type;
        }
        public bool IsNumber()
        {
            return NUM_TOKEN == m_Type;
        }
        public bool IsString()
        {
            return STRING_TOKEN == m_Type;
        }
        public void Clear()
        {
            m_Type = ID_TOKEN;
            m_Id = string.Empty;
            m_Line = -1;
        }
        public void CopyFrom(ValueData other)
        {
            m_Type = other.m_Type;
            m_Id = other.m_Id;
            m_Line = other.m_Line;

            SetSeparator(other.GetSeparator());

            if (!DslFile.DontLoadComments) {
                CopyComments(other);
            }
        }

        public ValueData()
        { }
        public ValueData(string val)
        {
            if (val.StartsWith("0x") && uint.TryParse(val.Substring(2), System.Globalization.NumberStyles.HexNumber, null, out var vx))
                m_Type = NUM_TOKEN;
            else if (float.TryParse(val, System.Globalization.NumberStyles.Any, null, out var v) || int.TryParse(val, System.Globalization.NumberStyles.Any, null, out var v2))
                m_Type = NUM_TOKEN;
            else if (Utility.needQuote(val))
                m_Type = STRING_TOKEN;
            else
                m_Type = ID_TOKEN;

            m_Id = val;
            m_Line = -1;
        }
        public ValueData(string val, int _type)
        {
            m_Type = _type;
            m_Id = val;
            m_Line = -1;
        }

        private int m_Type = ID_TOKEN;
        private string m_Id = string.Empty;
        private int m_Line = -1;

        public static ValueData NullValue
        {
            get {
                s_Instance.Clear();
                return s_Instance;
            }
        }
        private static ValueData s_Instance = new ValueData();
    }
    /// <summary>
    /// 函数数据，可能出现在函数头、参数表中。
    /// </summary>
    public class FunctionData : ValueOrFunctionData
    {
        public enum ParamClassEnum
        {
            PARAM_CLASS_MIN = 0,
            PARAM_CLASS_NOTHING = PARAM_CLASS_MIN,
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
            PARAM_CLASS_STATEMENT,
            PARAM_CLASS_EXTERN_SCRIPT,
            PARAM_CLASS_PARENTHESIS_COLON,
            PARAM_CLASS_BRACKET_COLON,
            PARAM_CLASS_ANGLE_BRACKET_COLON,
            PARAM_CLASS_PARENTHESIS_PERCENT,
            PARAM_CLASS_BRACKET_PERCENT,
            PARAM_CLASS_BRACE_PERCENT,
            PARAM_CLASS_ANGLE_BRACKET_PERCENT,
            PARAM_CLASS_COLON_COLON,
            PARAM_CLASS_COLON_COLON_PARENTHESIS,
            PARAM_CLASS_COLON_COLON_BRACKET,
            PARAM_CLASS_COLON_COLON_BRACE,
            PARAM_CLASS_PERIOD_STAR,
            PARAM_CLASS_QUESTION_PERIOD_STAR,
            PARAM_CLASS_POINTER_STAR,
            PARAM_CLASS_OPERATOR,
            PARAM_CLASS_TERNARY_OPERATOR,
            PARAM_CLASS_MAX,
            PARAM_CLASS_WRAP_INFIX_CALL_MASK = 0x20,
            PARAM_CLASS_UNMASK = 0x1F,
        }
        public override bool IsValid()
        {
            return HaveId() || HaveParamOrStatement();
        }
        public override string GetId()
        {
            if (null != m_Name)
                return m_Name.GetId();
            else if (null != m_LowerOrderFunction)
                return m_LowerOrderFunction.GetId();
            else
                return string.Empty;
        }
        public override int GetIdType()
        {
            if (null != m_Name)
                return m_Name.GetIdType();
            else if (null != m_LowerOrderFunction)
                return m_LowerOrderFunction.GetIdType();
            else
                return ID_TOKEN;
        }
        public override int GetLine()
        {
            if (null != m_Name)
                return m_Name.GetLine();
            else if (null != m_LowerOrderFunction)
                return m_LowerOrderFunction.GetLine();
            else {
                foreach(var p in m_Params) {
                    int line = p.GetLine();
                    if (line >= 0)
                        return line;
                }
                return -1;
            }
        }
        public override string ToScriptString(bool includeComment)
        {
#if FULL_VERSION
            if (includeComment) {
                return CalcFirstComment() + Utility.getFunctionStringWithStrDefDelim(this, true) + CalcComment() + CalcLastComment();
            }
            else {
                return Utility.getFunctionStringWithStrDefDelim(this, true);
            }
#else
      return ToString();
#endif
        }
        public override bool HaveId()
        {
            if (null != m_Name)
                return m_Name.HaveId();
            else if (null != m_LowerOrderFunction)
                return m_LowerOrderFunction.HaveId();
            else
                return false;
        }

        public string CalcComment()
        {
            if (DslFile.DontLoadComments)
                return string.Empty;
            var cmtsInfo = GetFunctionCommentsInfo();
            if (null == cmtsInfo || null == cmtsInfo.m_Comments)
                return string.Empty;
            string cmt = string.Join(string.Empty, cmtsInfo.m_Comments.ToArray());
            if (null != m_LowerOrderFunction && !HaveStatement() && !HaveExternScript()) {
                cmt = m_LowerOrderFunction.CalcComment() + cmt;
            }
            return cmt;
        }
        public List<string> Comments
        {
            get {
                if (DslFile.DontLoadComments)
                    return NullSyntax.EmptyStringList;
                var cmtsInfo = GetFunctionCommentsInfo();
                if (null == cmtsInfo || null == cmtsInfo.m_Comments) {
                    cmtsInfo.m_Comments = new List<string>();
                }
                return cmtsInfo.m_Comments;
            }
        }

        public List<ISyntaxComponent> Params
        {
            get {
                PrepareParams();
                return m_Params;
            }
            set {
                m_Params = value;
                if (null == m_Params) {
                    m_ParamClass = (int)ParamClassEnum.PARAM_CLASS_NOTHING;
                }
                else if (m_Params.Count > 0) {
                    if ((int)ParamClassEnum.PARAM_CLASS_NOTHING == m_ParamClass) {
                        m_ParamClass = (int)ParamClassEnum.PARAM_CLASS_PARENTHESIS;
                    }
                }
            }
        }
        public bool IsHighOrder
        {
            get { return m_IsHighOrder; }
        }
        public ValueData Name
        {
            get {
                if (null != m_Name)
                    return m_Name;
                else
                    return ValueData.NullValue;
            }
            set {
                m_Name = value;
                m_LowerOrderFunction = null;
                m_IsHighOrder = false;
            }
        }
        public FunctionData LowerOrderFunction
        {
            get {
                if (null != m_LowerOrderFunction)
                    return m_LowerOrderFunction;
                else
                    return FunctionData.NullFunction;
            }
            set {
                m_Name = null;
                m_LowerOrderFunction = value;
                m_IsHighOrder = true;
            }
        }
        public FunctionData ThisOrLowerOrderCall
        {
            get {
                if (HaveParam())
                    return this;
                else if (HaveLowerOrderParam())
                    return m_LowerOrderFunction;
                else 
                    return FunctionData.NullFunction;
            }
        }
        public FunctionData ThisOrLowerOrderBody
        {
            get {
                if (HaveStatement())
                    return this;
                else if (HaveLowerOrderStatement())
                    return m_LowerOrderFunction;
                else 
                    return FunctionData.NullFunction;
            }
        }
        public FunctionData ThisOrLowerOrderScript
        {
            get {
                if (HaveExternScript())
                    return this;
                else if (HaveLowerOrderExternScript())
                    return m_LowerOrderFunction;
                else 
                    return FunctionData.NullFunction;
            }
        }
        public bool HaveLowerOrderParam()
        {
            if (null != m_LowerOrderFunction && m_LowerOrderFunction.HaveParam())
                return true;
            else
                return false;
        }
        public bool HaveLowerOrderStatement()
        {
            if (null != m_LowerOrderFunction && m_LowerOrderFunction.HaveStatement())
                return true;
            else
                return false;
        }
        public bool HaveLowerOrderExternScript()
        {
            if (null != m_LowerOrderFunction && m_LowerOrderFunction.HaveExternScript())
                return true;
            else
                return false;
        }
        public void SetParamClass(int type)
        {
            int innerType = type & (int)ParamClassEnum.PARAM_CLASS_UNMASK;
            if (innerType >= (int)ParamClassEnum.PARAM_CLASS_MIN && innerType < (int)ParamClassEnum.PARAM_CLASS_MAX) {
                m_ParamClass = type;
            }
        }
        public int GetParamClass()
        {
            return m_ParamClass;
        }
        public int GetParamClassUnmasked()
        {
            int paramClass = (m_ParamClass & (int)ParamClassEnum.PARAM_CLASS_UNMASK);
            return paramClass;
        }
        public bool HaveParamClassInfixFlag()
        {
            int infix = (m_ParamClass & (int)ParamClassEnum.PARAM_CLASS_WRAP_INFIX_CALL_MASK);
            return infix == (int)ParamClassEnum.PARAM_CLASS_WRAP_INFIX_CALL_MASK;
        }
        public bool IsOperatorParamClass()
        {
            int paramClass = GetParamClassUnmasked();
            return paramClass == (int)ParamClassEnum.PARAM_CLASS_OPERATOR;
        }
        public bool IsTernaryOperatorParamClass()
        {
            int paramClass = GetParamClassUnmasked();
            return paramClass == (int)ParamClassEnum.PARAM_CLASS_TERNARY_OPERATOR;
        }
        public bool IsMemberParamClass()
        {
            int paramClass = GetParamClassUnmasked();
            return paramClass == (int)ParamClassEnum.PARAM_CLASS_COLON_COLON ||
                paramClass == (int)ParamClassEnum.PARAM_CLASS_PERIOD ||
                paramClass == (int)ParamClassEnum.PARAM_CLASS_PERIOD_STAR ||
                paramClass == (int)ParamClassEnum.PARAM_CLASS_POINTER ||
                paramClass == (int)ParamClassEnum.PARAM_CLASS_POINTER_STAR ||
                paramClass == (int)ParamClassEnum.PARAM_CLASS_QUESTION_PERIOD ||
                paramClass == (int)ParamClassEnum.PARAM_CLASS_QUESTION_PERIOD_STAR;
        }
        public bool HaveParamOrStatement()
        {
            return (int)ParamClassEnum.PARAM_CLASS_NOTHING != m_ParamClass;
        }
        public bool HaveParam()
        {
            return HaveParamOrStatement() && !HaveStatement() && !HaveExternScript();
        }
        public bool HaveStatement()
        {
            return (int)ParamClassEnum.PARAM_CLASS_STATEMENT == m_ParamClass;
        }
        public bool HaveExternScript()
        {
            return (int)ParamClassEnum.PARAM_CLASS_EXTERN_SCRIPT == m_ParamClass;
        }
        public int GetParamNum()
        {
            if (null == m_Params)
                return 0;
            return m_Params.Count;
        }
        public void SetParam(int index, ISyntaxComponent data)
        {
            if (null == m_Params)
                return;
            if (index < 0 || index >= m_Params.Count)
                return;
            m_Params[index] = data;
        }
        public ISyntaxComponent GetParam(int index)
        {
            if (null == m_Params)
                return NullSyntax.Instance;
            if (index < 0 || index >= (int)m_Params.Count)
                return NullSyntax.Instance;
            return m_Params[index];
        }
        public string GetParamId(int index)
        {
            if (null == m_Params)
                return string.Empty;
            if (index < 0 || index >= (int)m_Params.Count)
                return string.Empty;
            return m_Params[index].GetId();
        }
        public void ClearParams()
        {
            PrepareParams();
            m_Params.Clear();
        }
        public void AddParam(string id)
        {
            PrepareParams();
            m_Params.Add(new ValueData(id));
            if ((int)ParamClassEnum.PARAM_CLASS_NOTHING == m_ParamClass) {
                m_ParamClass = (int)ParamClassEnum.PARAM_CLASS_PARENTHESIS;
            }
        }
        public void AddParam(string id, int type)
        {
            PrepareParams();
            m_Params.Add(new ValueData(id, type));
            if ((int)ParamClassEnum.PARAM_CLASS_NOTHING == m_ParamClass) {
                m_ParamClass = (int)ParamClassEnum.PARAM_CLASS_PARENTHESIS;
            }
        }
        public void AddParam(ValueData param)
        {
            PrepareParams();
            m_Params.Add(param);
            if ((int)ParamClassEnum.PARAM_CLASS_NOTHING == m_ParamClass) {
                m_ParamClass = (int)ParamClassEnum.PARAM_CLASS_PARENTHESIS;
            }
        }
        public void AddParam(FunctionData param)
        {
            PrepareParams();
            m_Params.Add(param);
            if ((int)ParamClassEnum.PARAM_CLASS_NOTHING == m_ParamClass) {
                m_ParamClass = (int)ParamClassEnum.PARAM_CLASS_PARENTHESIS;
            }
        }
        public void AddParam(StatementData param)
        {
            PrepareParams();
            m_Params.Add(param);
            if ((int)ParamClassEnum.PARAM_CLASS_NOTHING == m_ParamClass) {
                m_ParamClass = (int)ParamClassEnum.PARAM_CLASS_PARENTHESIS;
            }
        }
        public void AddParam(ISyntaxComponent param)
        {
            PrepareParams();
            m_Params.Add(param);
            if ((int)ParamClassEnum.PARAM_CLASS_NOTHING == m_ParamClass) {
                m_ParamClass = (int)ParamClassEnum.PARAM_CLASS_PARENTHESIS;
            }
        }
        public void Clear()
        {
            m_Name = null;
            m_LowerOrderFunction = null;
            m_IsHighOrder = false;
            m_Params = null;
            m_ParamClass = (int)ParamClassEnum.PARAM_CLASS_NOTHING;

            m_CommentsInfo = null;
        }
        public void CopyFrom(FunctionData other)
        {
            m_IsHighOrder = other.m_IsHighOrder;
            if (null != other.m_Name) {
                m_Name = Utility.CloneDsl(other.m_Name) as Dsl.ValueData;
                Debug.Assert(null != m_Name);
            }
            else {
                m_Name = null;
            }
            if (null != other.m_LowerOrderFunction) {
                m_LowerOrderFunction = Utility.CloneDsl(other.m_LowerOrderFunction) as Dsl.FunctionData;
                Debug.Assert(null != m_LowerOrderFunction);
            }
            else {
                m_LowerOrderFunction = null;
            }
            m_ParamClass = other.m_ParamClass;
            if (null != other.m_Params) {
                ClearParams();
                foreach (var p in other.m_Params) {
                    m_Params.Add(Utility.CloneDsl(p));
                }
            }
            else {
                m_Params = null;
            }

            SetSeparator(other.GetSeparator());

            if (!DslFile.DontLoadComments) {
                if (null != other.m_CommentsInfo && null != other.m_CommentsInfo.m_Comments) {
                    Comments.AddRange(other.m_CommentsInfo.m_Comments);
                }
                CopyComments(other);
            }
        }
        private void PrepareParams()
        {
            if (null == m_Params) {
                m_Params = new List<ISyntaxComponent>();
            }
        }
        internal override SyntaxComponentCommentsInfo GetCommentsInfo()
        {
            return GetFunctionCommentsInfo();
        }
        private FunctionCommentsInfo GetFunctionCommentsInfo()
        {
            if (DslFile.DontLoadComments)
                return null;
            if (null == m_CommentsInfo) {
                m_CommentsInfo = new FunctionCommentsInfo();
            }
            return m_CommentsInfo;
        }

        private bool m_IsHighOrder = false;
        private ValueData m_Name = null;
        private FunctionData m_LowerOrderFunction = null;
        private List<ISyntaxComponent> m_Params = null;
        private int m_ParamClass = (int)ParamClassEnum.PARAM_CLASS_NOTHING;

        private FunctionCommentsInfo m_CommentsInfo = null;

        public static FunctionData NullFunction
        {
            get {
                s_Instance.Clear();
                return s_Instance;
            }
        }
        private static FunctionData s_Instance = new FunctionData();
    }
    /// <summary>
    /// 语句数据，由多个函数项连接而成。
    /// </summary>
    /// <remarks>
    /// 备忘：为什么StatementData的成员不使用ISyntaxComponent[]而是FunctionData[]
    /// 1、虽然语法上这里的FunctionData可以退化为ValueData，但不可以是StatementData，这样在概念上不能与ISyntaxComponent等同
    /// 2、在设计上，FunctionData应该考虑到退化情形，尽量在退化情形不占用额外空间
    /// </remarks>
    public class StatementData : AbstractSyntaxComponent
    {
        public override bool IsValid()
        {
            bool ret = true;
            if (m_ValueOrFunctions.Count <= 0) {
                ret = false;
            }
            else {
                for (int i = 0; i < m_ValueOrFunctions.Count; ++i) {
                    ret = ret && m_ValueOrFunctions[i].IsValid();
                }
            }
            return ret;
        }
        public override string GetId()
        {
            if (m_ValueOrFunctions.Count <= 0)
                return string.Empty;
            else
                return m_ValueOrFunctions[0].GetId();
        }
        public override int GetIdType()
        {
            if (m_ValueOrFunctions.Count <= 0)
                return ID_TOKEN;
            else
                return m_ValueOrFunctions[0].GetIdType();
        }
        public override int GetLine()
        {
            if (m_ValueOrFunctions.Count <= 0)
                return -1;
            else {
                foreach (var item in m_ValueOrFunctions) {
                    int line = item.GetLine();
                    if (line >= 0)
                        return line;
                }
                return -1;
            }
        }
        public override string ToScriptString(bool includeComment)
        {
#if FULL_VERSION
            //与write方法不同，这里输出无缩进单行表示
            FunctionData tempData = First.AsFunction;
            FunctionData callData = null;
            if (null != tempData) {
                callData = tempData.LowerOrderFunction;
            }
            if (null != callData && tempData.IsTernaryOperatorParamClass()) {
                //三目表达式表示为op1(cond)(true_val)op2(false_val)
                if (callData.HaveId() && callData.HaveParamOrStatement()) {
                    string line = "/*[?:]*/";
                    if (Functions.Count == 2) {
                        FunctionData funcData = Functions[1].AsFunction;
                        if (null != funcData && funcData.HaveId() && funcData.HaveParamOrStatement()) {
                            line = string.Format("{0} {1} {2}", callData.GetParam(0).ToScriptString(includeComment), callData.GetId(), tempData.GetParam(0).ToScriptString(includeComment));
                            line = string.Format("{0} {1} {2}", line, funcData.GetId(), funcData.GetParam(0).ToScriptString(includeComment));
                        }
                    }
                    if (includeComment) {
                        return CalcFirstComment() + line + CalcLastComment();
                    }
                    else {
                        return line;
                    }
                }
                else {
                    if (includeComment) {
                        return CalcFirstComment() + CalcLastComment();
                    }
                    else {
                        return string.Empty;
                    }
                }
            }
            else {
                StringBuilder stream = new StringBuilder();
                if (includeComment) {
                    stream.Append(CalcFirstComment());
                }
                int ct = Functions.Count;
                for (int i = 0; i < ct; ++i) {
                    ValueOrFunctionData funcData = Functions[i];
                    stream.Append(funcData.ToScriptString(includeComment));
                }
                if (includeComment) {
                    stream.Append(CalcLastComment());
                }
                return stream.ToString();
            }
#else
      return ToString();
#endif
        }
        public override bool HaveId()
        {
            if (m_ValueOrFunctions.Count > 0)
                return m_ValueOrFunctions[0].HaveId();
            else
                return false;
        }

        public int GetFunctionNum()
        {
            return m_ValueOrFunctions.Count;
        }
        public void SetFunction(int index, ValueOrFunctionData funcData)
        {
            if (index < 0 || index >= m_ValueOrFunctions.Count)
                return;
            m_ValueOrFunctions[index] = funcData;
        }
        public ValueOrFunctionData GetFunction(int index)
        {
            if (index < 0 || index >= m_ValueOrFunctions.Count)
                return FunctionData.NullFunction;
            return m_ValueOrFunctions[index];
        }
        public string GetFunctionId(int index)
        {
            if (index < 0 || index >= m_ValueOrFunctions.Count)
                return string.Empty;
            return m_ValueOrFunctions[index].GetId();
        }
        public void AddFunction(ValueOrFunctionData funcData)
        {
            m_ValueOrFunctions.Add(funcData);
        }
        public List<ValueOrFunctionData> Functions
        {
            get { return m_ValueOrFunctions; }
        }
        public ValueOrFunctionData First
        {
            get {
                if (m_ValueOrFunctions.Count > 0)
                    return m_ValueOrFunctions[0];
                else
                    return ValueData.NullValue;
            }
        }
        public ValueOrFunctionData Second
        {
            get {
                if (m_ValueOrFunctions.Count > 1)
                    return m_ValueOrFunctions[1];
                else
                    return FunctionData.NullFunction;
            }
        }
        public ValueOrFunctionData Third
        {
            get {
                if (m_ValueOrFunctions.Count > 2)
                    return m_ValueOrFunctions[2];
                else
                    return FunctionData.NullFunction;
            }
        }
        public ValueOrFunctionData Last
        {
            get {
                if (m_ValueOrFunctions.Count > 0)
                    return m_ValueOrFunctions[m_ValueOrFunctions.Count - 1];
                else
                    return FunctionData.NullFunction;
            }
        }
        public void Clear()
        {
            m_ValueOrFunctions = new List<ValueOrFunctionData>();

            m_CommentsInfo = null;
        }
        public void CopyFrom(StatementData other)
        {
            m_ValueOrFunctions.Clear();
            foreach (var f in other.m_ValueOrFunctions) {
                var nf = Utility.CloneDsl(f);
                var v = nf as Dsl.ValueOrFunctionData;
                Debug.Assert(null != v);
                m_ValueOrFunctions.Add(v);
            }

            SetSeparator(other.GetSeparator());

            if (!DslFile.DontLoadComments) {
                CopyComments(other);
            }
        }
        internal override SyntaxComponentCommentsInfo GetCommentsInfo()
        {
            if (DslFile.DontLoadComments)
                return null;
            if (null == m_CommentsInfo) {
                m_CommentsInfo = new SyntaxComponentCommentsInfo();
            }
            return m_CommentsInfo;
        }

        private List<ValueOrFunctionData> m_ValueOrFunctions = new List<ValueOrFunctionData>();
        private SyntaxComponentCommentsInfo m_CommentsInfo = null;

        public static StatementData NullStatement
        {
            get {
                s_NullStatement.Clear();
                return s_NullStatement;
            }
        }
        private static StatementData s_NullStatement = new StatementData();
    }

    public class DslFile
    {
        public List<ISyntaxComponent> DslInfos
        {
            get { return mDslInfos; }
        }
        public void AddDslInfo(ISyntaxComponent data)
        {
            mDslInfos.Add(data);
        }

        public bool Load(string file, DslLogDelegation logCallback)
        {
            string content = File.ReadAllText(file);
            //logCallback(string.Format("DslFile.Load {0}:\n{1}", file, content));
            return LoadFromString(content, logCallback);
        }
        public bool LoadFromString(string content, DslLogDelegation logCallback)
        {
            content = Mac2Unix(content);

            mDslInfos.Clear();
            Common.DslLog log = new Common.DslLog();
            log.OnLog += logCallback;

            Parser.DslError error = new Parser.DslError(log);
            Common.DslAction action = new Common.DslAction(log, mDslInfos);
            Common.DslToken tokens = new Common.DslToken(action, log, content);
            tokens.OnGetToken = mOnGetToken;
            tokens.OnTokenCanEatQuestion = mOnTokenCanEatQuestion;

            action.onGetLastToken = () => { return tokens.getLastToken(); };
            action.onGetLastLineNumber = () => { return tokens.getLastLineNumber(); };
            action.onGetComment = (out bool commentOnNewLine) => { commentOnNewLine = tokens.IsCommentOnNewLine(); List<string> ret = new List<string>(); ret.AddRange(tokens.GetComments()); tokens.ResetComments(); return ret; };
            action.onSetStringDelimiter = (string begin, string end) => { tokens.setStringDelimiter(begin, end); };
            action.onSetScriptDelimiter = (string begin, string end) => { tokens.setScriptDelimiter(begin, end); };
            action.onBeforeAddFunction = mOnBeforeAddFunction;
            action.onAddFunction = mOnAddFunction;
            action.onBeforeEndStatement = mOnBeforeEndStatement;
            action.onEndStatement = mOnEndStatement;
            action.onBeforeBuildOperator = mOnBeforeBuildOperator;
            action.onBuildOperator = mOnBuildOperator;
            action.onSetFunctionId = mOnSetFunctionId;
            action.onSetMemberId = mOnSetMemberId;
            action.onBeforeBuildHighOrder = mOnBeforeBuildHighOrder;
            action.onBuildHighOrder = mOnBuildHighOrder;

            Parser.DslParser.parse(ref action, ref tokens, ref error, 0);
            if (log.HasError) {
                for (int i = 0; i < mDslInfos.Count; i++) {
                    mDslInfos.Clear();
                }
            }
            if (!string.IsNullOrEmpty(tokens.StringBeginDelimiter)) {
                mStringBeginDelimiter = tokens.StringBeginDelimiter;
            }
            if (!string.IsNullOrEmpty(tokens.StringEndDelimiter)) {
                mStringEndDelimiter = tokens.StringEndDelimiter;
            }
            if (!string.IsNullOrEmpty(tokens.ScriptBeginDelimiter)) {
                mScriptBeginDelimiter = tokens.ScriptBeginDelimiter;
            }
            if (!string.IsNullOrEmpty(tokens.ScriptEndDelimiter)) {
                mScriptEndDelimiter = tokens.ScriptEndDelimiter;
            }
            return !log.HasError;
        }
        public void Save(string file)
        {
#if FULL_VERSION
            StringBuilder sb = new StringBuilder();
            if(mStringBeginDelimiter!="\"" || mStringEndDelimiter != "\"") {
                sb.AppendFormat("@@delimiter(string, \"{0}\", \"{1}\");", mStringBeginDelimiter, mStringEndDelimiter);
                sb.AppendLine();
            }
            if (mScriptBeginDelimiter != "{:" || mScriptEndDelimiter != ":}") {
                sb.AppendFormat("@@delimiter(script, \"{0}\", \"{1}\");", mScriptBeginDelimiter, mScriptEndDelimiter);
                sb.AppendLine();
            }
            for (int i = 0; i < mDslInfos.Count; i++) {
                Utility.writeSyntaxComponent(sb, mDslInfos[i], 0, true, true, new DelimiterInfo(mStringBeginDelimiter, mStringEndDelimiter, mScriptBeginDelimiter, mScriptEndDelimiter));
            }
            File.WriteAllText(file, sb.ToString());
#endif
        }
        public string ToScriptString()
        {
#if FULL_VERSION
            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < mDslInfos.Count; i++) {
                Utility.writeSyntaxComponent(sb, mDslInfos[i], 0, true, false, new DelimiterInfo(mStringBeginDelimiter, mStringEndDelimiter, mScriptBeginDelimiter, mScriptEndDelimiter));
            }
            return sb.ToString();
#else
            return ToString();
#endif
        }

        public void LoadBinaryFile(string file, List<string> reuseKeyBuffer, List<string> reuseIdBuffer)
        {
            var code = File.ReadAllBytes(file);
            LoadBinaryCode(code, reuseKeyBuffer, reuseIdBuffer);
        }
        public void LoadBinaryCode(byte[] binaryCode, List<string> reuseKeyBuffer, List<string> reuseIdBuffer)
        {
            mDslInfos.Clear();
            if (null == binaryCode)
                return;
            int pos = c_BinaryIdentity.Length;
            int bytesLen = Utility.readInt(binaryCode, pos);
            pos += 4;
            int bytes2Len = Utility.readInt(binaryCode, pos);
            pos += 4;
            int keyCount = Utility.readInt(binaryCode, pos);
            pos += 4;
            int bytesStart = pos;
            int bytes2Start = bytesStart + bytesLen;
            int keyStart = bytes2Start + bytes2Len;
            if (reuseKeyBuffer.Capacity < keyCount)
                reuseKeyBuffer.Capacity = keyCount;
            reuseKeyBuffer.Clear();
            List<string> keys = reuseKeyBuffer;
            pos = keyStart;
            for (int i = 0; i < keyCount; ++i) {
                int byteCount;
                int len = Utility.read7BitEncodedInt(binaryCode, pos, out byteCount);
                if (len >= 0) {
                    pos += byteCount;
                    var key = Encoding.UTF8.GetString(binaryCode, pos, len);
                    keys.Add(key);
                    pos += len;
                }
                else {
                    break;
                }
            }
            if (reuseIdBuffer.Capacity < bytes2Len)
                reuseIdBuffer.Capacity = bytes2Len;
            reuseIdBuffer.Clear();
            List<string> identifiers = reuseIdBuffer;
            for (int i = bytes2Start; i < bytes2Start + bytes2Len && i < binaryCode.Length; ++i) {
                int byteCount;
                int ix = Utility.read7BitEncodedInt(binaryCode, i, out byteCount);
                if (ix >= 0) {
                    i += byteCount - 1;
                }
                else {
                    break;
                }
                if (ix >= 0 && ix < keys.Count) {
                    identifiers.Add(keys[ix]);
                }
                else {
                    identifiers.Add(string.Empty);
                }
            }
            List<ISyntaxComponent> infos = Utility.readBinary(binaryCode, bytesStart, bytesLen, identifiers);
            mDslInfos.AddRange(infos);
        }
        public void SaveBinaryFile(string file)
        {
#if FULL_VERSION
            MemoryStream stream = new MemoryStream();
            List<string> identifiers = new List<string>();
            foreach (ISyntaxComponent info in DslInfos) {
                Utility.writeBinary(stream, identifiers, info);
            }

            if (null == mStringComparer) {
                mStringComparer = new MyStringComparer();
            }
            byte[] bytes = stream.ToArray();
            SortedDictionary<string, int> dict = new SortedDictionary<string, int>(mStringComparer);
            int ct = identifiers.Count;
            for (int i = 0; i < ct; ++i) {
                string key = identifiers[i];
                if (!dict.ContainsKey(key)) {
                    dict.Add(key, 0);
                }
            }
            List<string> keys = new List<string>(dict.Keys);
            byte[] bytes2;
            using (MemoryStream ms = new MemoryStream()) {
                for (int i = 0; i < ct; ++i) {
                    string key = identifiers[i];
                    int ix = keys.BinarySearch(key, mStringComparer);
                    Utility.write7BitEncodedInt(ms, ix);
                }
                bytes2 = ms.ToArray();
            }
            using (MemoryStream bdsl = new MemoryStream()) {
                bdsl.Write(BinaryIdentity, 0, c_BinaryIdentity.Length);
                Utility.writeInt(bdsl, bytes.Length);
                Utility.writeInt(bdsl, bytes2.Length);
                Utility.writeInt(bdsl, keys.Count);
                bdsl.Write(bytes, 0, bytes.Length);
                bdsl.Write(bytes2, 0, bytes2.Length);
                foreach (var str in keys) {
                    var bstr = Encoding.UTF8.GetBytes(str);
                    Utility.write7BitEncodedInt(bdsl, bstr.Length);
                    bdsl.Write(bstr, 0, bstr.Length);
                }
                using (FileStream fs = new FileStream(file, FileMode.Create)) {
                    fs.Write(bdsl.GetBuffer(), 0, (int)bdsl.Length);
                    fs.Close();
                }
            }
#endif
        }

        public bool LoadLua(string file, DslLogDelegation logCallback)
        {
            string content = File.ReadAllText(file);
            //logCallback(string.Format("DslFile.Load {0}:\n{1}", file, content));
            return LoadLuaFromString(content, logCallback);
        }
        public bool LoadLuaFromString(string content, DslLogDelegation logCallback)
        {
            content = Mac2Unix(content);

            mDslInfos.Clear();
            Common.DslLog log = new Common.DslLog();
            log.OnLog += logCallback;
            Dsl.Parser.LuaToken tokens = new Dsl.Parser.LuaToken(log, content);
            Dsl.Parser.LuaError error = new Dsl.Parser.LuaError(log);
            Common.DslAction action = new Common.DslAction(log, mDslInfos);
            action.Type = Common.DslActionType.Lua;
            action.onGetLastToken = () => { return tokens.getLastToken(); };
            action.onGetLastLineNumber = () => { return tokens.getLastLineNumber(); };
            action.onGetComment = (out bool commentOnNewLine) => { commentOnNewLine = tokens.IsCommentOnNewLine(); List<string> ret = new List<string>(); ret.AddRange(tokens.GetComments()); tokens.ResetComments(); return ret; };
            
            Dsl.Parser.LuaParser.parse(ref action, ref tokens, ref error, 0);
            if (log.HasError) {
                for (int i = 0; i < mDslInfos.Count; i++) {
                    mDslInfos.Clear();
                }
            }
            return !log.HasError;
        }

        public bool LoadCpp(string file, DslLogDelegation logCallback)
        {
            string content = File.ReadAllText(file);
            //logCallback(string.Format("DslFile.Load {0}:\n{1}", file, content));
            return LoadCppFromString(content, logCallback);
        }
        public bool LoadCppFromString(string content, DslLogDelegation logCallback)
        {
            content = Mac2Unix(content);

            mDslInfos.Clear();
            Common.DslLog log = new Common.DslLog();
            log.OnLog += logCallback;

            Parser.CppError error = new Parser.CppError(log);
            Common.DslAction action = new Common.DslAction(log, mDslInfos);
            Common.CppToken tokens = new Common.CppToken(action, log, content);
            tokens.OnGetToken = mOnGetCppToken;
            tokens.OnTokenCanEatQuestion = mOnTokenCanEatQuestion;

            action.Type = Common.DslActionType.Cpp;
            action.onGetLastToken = () => { return tokens.getLastToken(); };
            action.onGetLastLineNumber = () => { return tokens.getLastLineNumber(); };
            action.onBeforeAddFunction = mOnBeforeAddFunction;
            action.onAddFunction = mOnAddFunction;
            action.onBeforeEndStatement = mOnBeforeEndStatement;
            action.onEndStatement = mOnEndStatement;
            action.onBeforeBuildOperator = mOnBeforeBuildOperator;
            action.onBuildOperator = mOnBuildOperator;
            action.onSetFunctionId = mOnSetFunctionId;
            action.onSetMemberId = mOnSetMemberId;
            action.onBeforeBuildHighOrder = mOnBeforeBuildHighOrder;
            action.onBuildHighOrder = mOnBuildHighOrder;

            Parser.CppParser.parse(ref action, ref tokens, ref error, 0);
            if (log.HasError) {
                for (int i = 0; i < mDslInfos.Count; i++) {
                    mDslInfos.Clear();
                }
            }
            return !log.HasError;
        }

        public bool LoadGpp(string file, DslLogDelegation logCallback)
        {
            string dummy;
            return LoadGpp(file, logCallback, string.Empty, string.Empty, out dummy);
        }
        public bool LoadGpp(string file, DslLogDelegation logCallback, string beginDelim, string endDelim)
        {
            string dummy;
            return LoadGpp(file, logCallback, beginDelim, endDelim, out dummy);
        }
        public bool LoadGpp(string file, DslLogDelegation logCallback, string beginDelim, string endDelim, out string transformedContent)
        {
            string content = File.ReadAllText(file);
            //logCallback(string.Format("DslFile.Load {0}:\n{1}", file, content));
            return LoadGppFromString(content, logCallback, beginDelim, endDelim, out transformedContent);
        }
        public bool LoadGppFromString(string content, DslLogDelegation logCallback)
        {
            string dummy;
            return LoadGppFromString(content, logCallback, string.Empty, string.Empty, out dummy);
        }
        public bool LoadGppFromString(string content, DslLogDelegation logCallback, string beginDelim, string endDelim)
        {
            string dummy;
            return LoadGppFromString(content, logCallback, beginDelim, endDelim, out dummy);
        }
        public bool LoadGppFromString(string content, DslLogDelegation logCallback, string beginDelim, string endDelim, out string transformedContent)
        {
            content = Mac2Unix(content);
            transformedContent = TransformPreprocess(content, beginDelim, endDelim);
            return LoadFromString(transformedContent, logCallback);
        }

        public void SetStringDelimiter(string begin, string end)
        {
            mStringBeginDelimiter = begin;
            mStringEndDelimiter = end;
        }
        public void SetScriptDelimiter(string begin, string end)
        {
            mScriptBeginDelimiter = begin;
            mScriptEndDelimiter = end;
        }
        public string StringBeginDelimiter
        {
            get { return mStringBeginDelimiter; }
        }
        public string StringEndDelimiter
        {
            get { return mStringEndDelimiter; }
        }
        public string ScriptBeginDelimiter
        {
            get { return mScriptBeginDelimiter; }
        }
        public string ScriptEndDelimiter
        {
            get { return mScriptEndDelimiter; }
        }
        public Dsl.Common.GetCppTokenDelegation onGetCppToken
        {
            get { return mOnGetCppToken; }
            set { mOnGetCppToken = value; }
        }
        public Dsl.Common.GetTokenDelegation onGetToken
        {
            get { return mOnGetToken; }
            set { mOnGetToken = value; }
        }
        public Dsl.Common.BeforeAddFunctionDelegation onBeforeAddFunction
        {
            get { return mOnBeforeAddFunction; }
            set { mOnBeforeAddFunction = value; }
        }
        public Dsl.Common.AddFunctionDelegation onAddFunction
        {
            get { return mOnAddFunction; }
            set { mOnAddFunction = value; }
        }
        public Dsl.Common.BeforeEndStatementDelegation onBeforeEndStatement
        {
            get { return mOnBeforeEndStatement; }
            set { mOnBeforeEndStatement = value; }
        }
        public Dsl.Common.EndStatementDelegation onEndStatement
        {
            get { return mOnEndStatement; }
            set { mOnEndStatement = value; }
        }
        public Dsl.Common.BeforeBuildOperatorDelegation onBeforeBuildOperator
        {
            get { return mOnBeforeBuildOperator; }
            set { mOnBeforeBuildOperator = value; }
        }
        public Dsl.Common.BuildOperatorDelegation onBuildOperator
        {
            get { return mOnBuildOperator; }
            set { mOnBuildOperator = value; }
        }
        public Dsl.Common.SetFunctionIdDelegation onSetFunctionId
        {
            get { return mOnSetFunctionId; }
            set { mOnSetFunctionId = value; }
        }
        public Dsl.Common.SetMemberIdDelegation onSetMemberId
        {
            get { return mOnSetMemberId; }
            set { mOnSetMemberId = value; }
        }
        public Dsl.Common.BeforeBuildHighOrderDelegation onBeforeBuildHighOrder
        {
            get { return mOnBeforeBuildHighOrder; }
            set { mOnBeforeBuildHighOrder = value; }
        }
        public Dsl.Common.BuildHighOrderDelegation onBuildHighOrder
        {
            get { return mOnBuildHighOrder; }
            set { mOnBuildHighOrder = value; }
        }

        private static string TransformPreprocess(string input, string beginDelim, string endDelim)
        {
            var sb = new StringBuilder();
            if(!string.IsNullOrEmpty(beginDelim) && !string.IsNullOrEmpty(endDelim)) {
                sb.AppendFormat("@@delimiter(script, \"{0}\", \"{1}\");", beginDelim, endDelim);
                sb.AppendLine();
            }
            else {
                beginDelim = "{:";
                endDelim = ":}";
            }
            var tokenBuilder = new StringBuilder();
            bool codeBlockNeedClose = false;
            for (int i = 0; i < input.Length; ++i) {
                char ch = input[i];
                switch (ch) {
                    case '/': {
                            TryEmitStartCodeBlock(sb, beginDelim, ref codeBlockNeedClose);
                            sb.Append(ch);
                            if (i + 1 < input.Length) {
                                char c = input[i + 1];
                                if (c == '/') {
                                    sb.Append(c);
                                    for (int j = i + 2; j < input.Length; ++j) {
                                        c = input[j];
                                        sb.Append(c);
                                        if (c == '\n') {
                                            i = j;
                                            break;
                                        }
                                        else if (j == input.Length - 1) {
                                            i = j;
                                        }
                                    }
                                }
                                else if (c == '*') {
                                    sb.Append(c);
                                    char lc = '\0';
                                    for (int j = i + 2; j < input.Length; ++j) {
                                        c = input[j];
                                        sb.Append(c);
                                        if (lc == '*' && c == '/') {
                                            i = j;
                                            break;
                                        }
                                        lc = c;
                                    }
                                }
                            }
                        }
                        break;
                    case '\'':
                    case '"': {
                            TryEmitStartCodeBlock(sb, beginDelim, ref codeBlockNeedClose);
                            sb.Append(ch);
                            for (int j = i + 1; j < input.Length; ++j) {
                                char c = input[j];
                                sb.Append(c);
                                if (c == '\\') {
                                    ++j;
                                    if (j < input.Length) {
                                        c = input[j];
                                        sb.Append(c);
                                    }
                                    else {
                                        i = j - 1;
                                        break;
                                    }
                                }
                                else if (c == ch) {
                                    i = j;
                                    break;
                                }
                            }
                        }
                        break;
                    case '#': {
                            //预处理（define, undef, include, if, ifdef, ifndef, else, elif, elifdef, elifndef (since C++23), endif, line, error, pragma）
                            int j = i + 1;
                            tokenBuilder.Length = 0;
                            bool isSkip = true;
                            for (; isSkip && j < input.Length;) {
                                bool s1 = SkipWhiteSpaces(input, ref j);
                                bool s2 = SkipComments(input, ref j);
                                isSkip = s1 || s2;
                            }
                            for (; j < input.Length && char.IsLetter(input[j]); ++j) {
                                tokenBuilder.Append(input[j]);
                            }
                            string key = tokenBuilder.ToString();
                            tokenBuilder.Length = 0;
                            string arg = string.Empty;
                            for (; j < input.Length && input[j] != '\n' && char.IsWhiteSpace(input[j]); ++j) ;
                            if (j < input.Length && input[j] != '\n') {
                                bool isExpression = key == "define" || key.Length >= 2 && (key[0] == 'i' && key[1] == 'f' || key[0] == 'e' && key[1] == 'l' || key[0] == 'e' && key[1] == 'n');
                                char lc = '\0';
                                for (; j < input.Length; ++j) {
                                    SkipComments(input, ref j);
                                    if (j >= input.Length)
                                        break;
                                    char cc = input[j];
                                    if (cc == '\r' && lc != '\\' || cc == '\n' && lc != '\r' && lc != '\\') {
                                        if (cc == '\r')
                                            ++j;
                                        arg = tokenBuilder.ToString().Trim();
                                        break;
                                    }
                                    if (isExpression && (cc == '"' || cc == '\'')) {
                                        //字符串
                                        tokenBuilder.Append(cc);
                                        ++j;
                                        while (j + 1 < input.Length && input[j] != cc) {
                                            char c = input[j];
                                            tokenBuilder.Append(c);
                                            ++j;
                                            if (c == '\\') {
                                                tokenBuilder.Append(input[j]);
                                                ++j;
                                            }
                                        }
                                        tokenBuilder.Append(input[j]);
                                    }
                                    else if (cc == '\\' && (input[j + 1] == '\r' || input[j + 1] == '\n')) {
                                        //续行符不输出
                                    }
                                    else {
                                        tokenBuilder.Append(cc);
                                    }
                                    lc = input[j];
                                }
                            }
                            TryEmitCloseCodeBlock(sb, endDelim, ref codeBlockNeedClose);
                            if (key.Length >= 2 && (key[0] == 'i' && key[1] == 'f' || key[0] == 'e' && key[1] == 'l' || key[0] == 'e' && key[1] == 'n')) {
                                //语句块
                                if (key[0] == 'i' && key[1] == 'f') {
                                    sb.Append("@@");
                                    sb.Append(key);
                                    sb.Append('(');
                                    sb.Append(arg);
                                    sb.Append(')');
                                    sb.AppendLine();
                                    sb.Append("{");
                                    sb.AppendLine();
                                }
                                else if (key[0] == 'e' && key[1] == 'l') {
                                    sb.Append("}");
                                    sb.AppendLine();
                                    sb.Append("@@");
                                    sb.Append(key);
                                    sb.Append('(');
                                    sb.Append(arg);
                                    sb.Append(')');
                                    sb.AppendLine();
                                    sb.Append("{");
                                    sb.AppendLine();
                                }
                                else {
                                    sb.Append("}");
                                    sb.AppendLine();
                                    sb.Append("@@");
                                    sb.Append(key);
                                    sb.Append('(');
                                    sb.Append(arg);
                                    sb.Append(')');
                                    sb.AppendLine();
                                }
                            }
                            else {
                                //函数
                                sb.Append("@@");
                                if (string.IsNullOrEmpty(key))
                                    sb.Append("ignore");
                                else
                                    sb.Append(key);
                                sb.Append('(');
                                if (key == "define" && IsSimpleDefine(arg) || key == "undef") {
                                    sb.Append(arg);
                                }
                                else {
                                    string quoteArg = Utility.quoteStringWithStrDefDelim(arg, Dsl.FunctionData.STRING_TOKEN);
                                    sb.Append(quoteArg);
                                }
                                sb.Append(')');
                                sb.Append(';');
                                sb.AppendLine();
                            }
                            i = j;
                        }
                        break;
                    case ' ':
                    case '\t':
                    case '\r':
                    case '\n':
                        TryEmitStartCodeBlock(sb, beginDelim, ref codeBlockNeedClose);
                        sb.Append(ch);
                        break;
                    default:
                        TryEmitStartCodeBlock(sb, beginDelim, ref codeBlockNeedClose);
                        sb.Append(ch);
                        break;
                }
            }
            if (!char.IsWhiteSpace(sb[sb.Length - 1])) {
                sb.AppendLine();
            }
            TryEmitCloseCodeBlock(sb, endDelim, ref codeBlockNeedClose);
            return sb.ToString();
        }
        private static void TryEmitStartCodeBlock(StringBuilder sb, string delim, ref bool codeBlockNeedClose)
        {
            if (!codeBlockNeedClose) {
                sb.Append("@@code");
                sb.AppendLine();
                sb.Append(delim);
                sb.AppendLine();
                codeBlockNeedClose = true;
            }
        }
        private static void TryEmitCloseCodeBlock(StringBuilder sb, string delim, ref bool codeBlockNeedClose)
        {
            if (codeBlockNeedClose) {
                sb.Append(delim);
                sb.Append(';');
                sb.AppendLine();
                codeBlockNeedClose = false;
            }
        }
        private static bool SkipWhiteSpaces(string input, ref int ix)
        {
            bool isSkip = false;
            for (; ix < input.Length && input[ix] != '\n' && char.IsWhiteSpace(input[ix]); ++ix) {
                isSkip = true;
            }
            return isSkip;
        }
        private static bool SkipComments(string input, ref int ix)
        {
            bool isSkip = false;
            //单行注释
            if (ix + 1 < input.Length && input[ix] == '/' && input[ix + 1] == '/') {
                for (; ix < input.Length && input[ix] != '\n'; ++ix) ;
                isSkip = true;
            }
            //多行注释
            if (ix + 1 < input.Length && input[ix] == '/' && input[ix + 1] == '*') {
                ++ix;
                ++ix;
                for (; ix + 1 < input.Length; ++ix) {
                    if (input[ix] == '*' && input[ix + 1] == '/') {
                        ++ix;
                        ++ix;
                        break;
                    }
                }
                isSkip = true;
            }
            return isSkip;
        }
        private static bool IsSimpleDefine(string str)
        {
            for (int i = 0; i < str.Length; ++i) {
                char c = str[i];
                if (!char.IsLetterOrDigit(c) && c != '_' && c != ' ' && c != '\t')
                    return false;
            }
            return true;
        }

        private class MyStringComparer : IComparer<string>
        {
            public int Compare(string x, string y)
            {
                if (object.ReferenceEquals(x, y)) {
                    return 0;
                }
                if (x == null) {
                    return -1;
                }
                if (y == null) {
                    return 1;
                }

                if (x.Length < y.Length)
                    return -1;
                else if (x.Length > y.Length)
                    return 1;
                else
                    return string.CompareOrdinal(x, y);
            }
        }

        private MyStringComparer mStringComparer = null;
        private List<ISyntaxComponent> mDslInfos = new List<ISyntaxComponent>();
        private string mStringBeginDelimiter = "\"";
        private string mStringEndDelimiter = "\"";
        private string mScriptBeginDelimiter = "{:";
        private string mScriptEndDelimiter = ":}";

        private Dsl.Common.TokenCanEatQuestionDelegation mOnTokenCanEatQuestion;
        private Dsl.Common.GetCppTokenDelegation mOnGetCppToken;
        private Dsl.Common.GetTokenDelegation mOnGetToken;
        private Dsl.Common.BeforeAddFunctionDelegation mOnBeforeAddFunction;
        private Dsl.Common.AddFunctionDelegation mOnAddFunction;
        private Dsl.Common.BeforeEndStatementDelegation mOnBeforeEndStatement;
        private Dsl.Common.EndStatementDelegation mOnEndStatement;
        private Dsl.Common.BeforeBuildOperatorDelegation mOnBeforeBuildOperator;
        private Dsl.Common.BuildOperatorDelegation mOnBuildOperator;
        private Dsl.Common.SetFunctionIdDelegation mOnSetFunctionId;
        private Dsl.Common.SetMemberIdDelegation mOnSetMemberId;
        private Dsl.Common.BeforeBuildHighOrderDelegation mOnBeforeBuildHighOrder;
        private Dsl.Common.BuildHighOrderDelegation mOnBuildHighOrder;

        public static byte[] BinaryIdentity
        {
            get {
                if (null == sBinaryIdentity) {
                    sBinaryIdentity = Encoding.ASCII.GetBytes(c_BinaryIdentity);
                }
                return sBinaryIdentity;
            }
        }
        public static bool DontLoadComments
        {
            get {
                return sDontLoadComments;
            }
            set {
                sDontLoadComments = value;
            }
        }
        public static bool IsBinaryDsl(byte[] data, int start)
        {
            if (null == data || data.Length < c_BinaryIdentity.Length)
                return false;
            bool r = true;
            for (int i = 0; i < BinaryIdentity.Length && start + i < data.Length; ++i) {
                if (BinaryIdentity[i] != data[start + i]) {
                    r = false;
                    break;
                }
            }
            return r;
        }

        public static string Mac2Unix(string txt)
        {
            int ix = txt.IndexOf('\r');
            if (ix >= 0 && ix + 1 < txt.Length && txt[ix + 1] != '\n') {
                return txt.Replace('\r', '\n');
            }
            return txt;
        }
        public static string Text2Dos(string txt)
        {
            int ix = txt.IndexOf('\n');
            if (ix > 0) {
                if (txt[ix - 1] != '\r')
                    return txt.Replace("\n", "\r\n");
            }
            else {
                ix = txt.IndexOf('\r');
                if (ix >= 0)
                    return txt.Replace("\r", "\r\n");
            }
            return txt;
        }
        public static string Text2Unix(string txt)
        {
            int ix = txt.IndexOf('\r');
            if (ix >= 0) {
                if (ix + 1 < txt.Length && txt[ix + 1] == '\n')
                    return txt.Replace("\r\n", "\n");
                else
                    return txt.Replace('\r', '\n');
            }
            return txt;
        }
        public static string Text2Mac(string txt)
        {
            int ix = txt.IndexOf('\n');
            if (ix > 0) {
                if (txt[ix - 1] != '\r')
                    return txt.Replace('\n', '\r');
                else
                    return txt.Replace("\r\n", "\r");
            }
            return txt;
        }

        public const string c_BinaryIdentity = "BDSL";

        private static byte[] sBinaryIdentity = null;
        private static bool sDontLoadComments = false;
    };

    public sealed class DelimiterInfo
    {
        public string StringBeginDelimiter = "\"";
        public string StringEndDelimiter = "\"";
        public string ScriptBeginDelimiter = "{:";
        public string ScriptEndDelimiter = ":}";

        public DelimiterInfo() { }
        public DelimiterInfo(string strBeginDelim, string strEndDelim, string scpBeginDelim, string scpEndDelim)
        {
            StringBeginDelimiter = strBeginDelim;
            StringEndDelimiter = strEndDelim;
            ScriptBeginDelimiter = scpBeginDelim;
            ScriptEndDelimiter = scpEndDelim;
        }
    }
    public sealed class Utility
    {
        public static string CheckCppParseTable()
        {
            var checker = new CppParseTableChecker();
            Dsl.Parser.CppParser.Accept(checker);
            return checker.GetResults();
        }

        public static Dsl.ISyntaxComponent CloneDsl(Dsl.ISyntaxComponent syntax)
        {
            Dsl.ISyntaxComponent ret;
            var vd = syntax as Dsl.ValueData;
            if (null != vd) {
                var nvd = new Dsl.ValueData();
                nvd.CopyFrom(vd);
                ret = nvd;
            }
            else {
                var fd = syntax as Dsl.FunctionData;
                if (null != fd) {
                    var nfd = new Dsl.FunctionData();
                    nfd.CopyFrom(fd);
                    ret = nfd;
                }
                else {
                    var sd = syntax as Dsl.StatementData;
                    if (null != sd) {
                        var nsd = new Dsl.StatementData();
                        nsd.CopyFrom(sd);
                        ret = nsd;
                    }
                    else {
                        ret = Dsl.NullSyntax.Instance;
                    }
                }
            }
            return ret;
        }

        internal static int readInt(byte[] bytes, int pos)
        {
            if (null != bytes && pos >= 0 && pos + 3 < bytes.Length) {
                return bytes[pos] | (bytes[pos + 1] << 8) | (bytes[pos + 2] << 16) | (bytes[pos + 3] << 24);
            }
            else {
                return -1;
            }
        }
        internal static int read7BitEncodedInt(byte[] bytes, int pos, out int byteCount)
        {
            int num = -1;
            byteCount = 0;
            if (null != bytes && pos < bytes.Length) {
                int bitCount = 0;
                byte b;
                num = 0;
                do {
                    if (bitCount == 35) {
                        num = -1;
                        break;
                    }
                    b = bytes[pos++];
                    num |= (b & 0x7F) << bitCount;
                    bitCount += 7;
                }
                while (pos < bytes.Length && (b & 0x80) != 0);
                byteCount = bitCount / 7;
            }
            return num;
        }
        internal static void writeInt(Stream s, int val)
        {
            byte b1 = (byte)val;
            byte b2 = (byte)(val >> 8);
            byte b3 = (byte)(val >> 16);
            byte b4 = (byte)(val >> 24);
            s.WriteByte(b1);
            s.WriteByte(b2);
            s.WriteByte(b3);
            s.WriteByte(b4);
        }
        internal static void write7BitEncodedInt(Stream s, int val)
        {
            uint num;
            for (num = (uint)val; num >= 128; num >>= 7) {
                s.WriteByte((byte)(num | 0x80));
            }
            s.WriteByte((byte)num);
        }

        public static void writeSyntaxComponent(StringBuilder stream, ISyntaxComponent data, int indent, bool firstLineNoIndent, bool isLastOfStatement, DelimiterInfo delim)
        {
#if FULL_VERSION
            ValueData val = data as ValueData;
            if (null != val) {
                writeValueData(stream, val, indent, firstLineNoIndent, isLastOfStatement);
            }
            else {
                FunctionData call = data as FunctionData;
                if (null != call) {
                    writeFunctionData(stream, call, indent, firstLineNoIndent, isLastOfStatement, delim);
                }
                else {
                    StatementData statement = data as StatementData;
                    writeStatementData(stream, statement, indent, firstLineNoIndent, isLastOfStatement, delim);
                }
            }
#endif
        }

        public static void writeValueData(StringBuilder stream, ValueData data, int indent, bool firstLineNoIndent, bool isLastOfStatement)
        {
#if FULL_VERSION
            writeFirstComments(stream, data, indent, firstLineNoIndent);
            writeText(stream, data.ToScriptString(false), firstLineNoIndent ? 0 : indent);
            if (isLastOfStatement)
                stream.Append(data.GetSepChar());
            writeLastComments(stream, data, indent, isLastOfStatement);
#endif
        }

        public static void writeFunctionData(StringBuilder stream, FunctionData data, int indent, bool firstLineNoIndent, bool isLastOfStatement, DelimiterInfo delim)
        {
#if FULL_VERSION
            //string lineNo = string.Format("/* {0} */", data.GetLine());
            //writeLine(stream, lineNo, indent);
            writeFirstComments(stream, data, indent, firstLineNoIndent);
            if (data.HaveParamOrStatement()) {
                if (data.IsOperatorParamClass()) {
                    int paramNum = data.GetParamNum();
                    if (paramNum == 1) {
                        writeText(stream, string.Empty, firstLineNoIndent ? 0 : indent);
                        if (data.IsHighOrder) {
                            writeFunctionData(stream, data.LowerOrderFunction, indent, paramNum > 0 ? true : firstLineNoIndent, false, delim);
                        }
                        else if (data.HaveId()) {
                            string op = data.GetId();
                            if (data.HaveParamClassInfixFlag())
                                op = "`" + op;
                            string line = quoteString(op, data.GetIdType(), delim.StringBeginDelimiter, delim.StringEndDelimiter);
                            writeText(stream, line, paramNum > 0 ? 0 : (firstLineNoIndent ? 0 : indent));
                        }
                        writeText(stream, " ", 0);
                        writeSyntaxComponent(stream, data.GetParam(0), indent, true, false, delim);
                    }
                    else {
                        if (paramNum > 0) {
                            writeSyntaxComponent(stream, data.GetParam(0), indent, firstLineNoIndent, false, delim);
                            writeText(stream, " ", 0);
                        }
                        if (data.IsHighOrder) {
                            writeFunctionData(stream, data.LowerOrderFunction, indent, paramNum > 0 ? true : firstLineNoIndent, false, delim);
                        }
                        else if (data.HaveId()) {
                            string op = data.GetId();
                            if (data.HaveParamClassInfixFlag())
                                op = "`" + op;
                            string line = quoteString(op, data.GetIdType(), delim.StringBeginDelimiter, delim.StringEndDelimiter);
                            writeText(stream, line, paramNum > 0 ? 0 : (firstLineNoIndent ? 0 : indent));
                        }
                        if (paramNum > 1) {
                            writeText(stream, " ", 0);
                            writeSyntaxComponent(stream, data.GetParam(1), indent, true, false, delim);
                        }
                    }
                }
                else {
                    if (data.IsHighOrder) {
                        writeFunctionData(stream, data.LowerOrderFunction, indent, firstLineNoIndent, false, delim);
                    }
                    else if (data.HaveId()) {
                        string line = quoteString(data.GetId(), data.GetIdType(), delim.StringBeginDelimiter, delim.StringEndDelimiter);
                        writeText(stream, line, firstLineNoIndent ? 0 : indent);
                    }
                    else {
                        writeText(stream, string.Empty, firstLineNoIndent ? 0 : indent);
                    }
                    if (data.HaveStatement() || data.HaveExternScript()) {
                        if (data.IsHighOrder) {
                            writeLastComments(stream, data.LowerOrderFunction, indent, false);
                        }
                        else if (data.HaveId()) {
                            writeLastComments(stream, data.Name, indent, false);
                        }
                        writeStatementsOrExternScript(stream, data, indent, delim);
                    }
                    else {
                        string lbracket = string.Empty;
                        string rbracket = string.Empty;
                        int paramClass = data.GetParamClassUnmasked();
                        switch (paramClass) {
                            case (int)FunctionData.ParamClassEnum.PARAM_CLASS_PARENTHESIS:
                                lbracket = "(";
                                rbracket = ")";
                                break;
                            case (int)FunctionData.ParamClassEnum.PARAM_CLASS_BRACKET:
                                lbracket = "[";
                                rbracket = "]";
                                break;
                            case (int)FunctionData.ParamClassEnum.PARAM_CLASS_PERIOD:
                                lbracket = ".";
                                rbracket = string.Empty;
                                break;
                            case (int)FunctionData.ParamClassEnum.PARAM_CLASS_PERIOD_PARENTHESIS:
                                lbracket = ".(";
                                rbracket = ")";
                                break;
                            case (int)FunctionData.ParamClassEnum.PARAM_CLASS_PERIOD_BRACKET:
                                lbracket = ".[";
                                rbracket = "]";
                                break;
                            case (int)FunctionData.ParamClassEnum.PARAM_CLASS_PERIOD_BRACE:
                                lbracket = ".{";
                                rbracket = "}";
                                break;
                            case (int)FunctionData.ParamClassEnum.PARAM_CLASS_COLON_COLON:
                                lbracket = "::";
                                rbracket = string.Empty;
                                break;
                            case (int)FunctionData.ParamClassEnum.PARAM_CLASS_COLON_COLON_PARENTHESIS:
                                lbracket = "::(";
                                rbracket = ")";
                                break;
                            case (int)FunctionData.ParamClassEnum.PARAM_CLASS_COLON_COLON_BRACKET:
                                lbracket = "::[";
                                rbracket = "]";
                                break;
                            case (int)FunctionData.ParamClassEnum.PARAM_CLASS_COLON_COLON_BRACE:
                                lbracket = "::{";
                                rbracket = "}";
                                break;
                            case (int)FunctionData.ParamClassEnum.PARAM_CLASS_QUESTION_PERIOD:
                                lbracket = "?.";
                                rbracket = string.Empty;
                                break;
                            case (int)FunctionData.ParamClassEnum.PARAM_CLASS_QUESTION_PARENTHESIS:
                                lbracket = "?(";
                                rbracket = ")";
                                break;
                            case (int)FunctionData.ParamClassEnum.PARAM_CLASS_QUESTION_BRACKET:
                                lbracket = "?[";
                                rbracket = "]";
                                break;
                            case (int)FunctionData.ParamClassEnum.PARAM_CLASS_QUESTION_BRACE:
                                lbracket = "?{";
                                rbracket = "}";
                                break;
                            case (int)FunctionData.ParamClassEnum.PARAM_CLASS_POINTER:
                                lbracket = "->";
                                rbracket = string.Empty;
                                break;
                            case (int)FunctionData.ParamClassEnum.PARAM_CLASS_BRACKET_COLON:
                                lbracket = "[:";
                                rbracket = ":]";
                                break;
                            case (int)FunctionData.ParamClassEnum.PARAM_CLASS_PARENTHESIS_COLON:
                                lbracket = "(:";
                                rbracket = ":)";
                                break;
                            case (int)FunctionData.ParamClassEnum.PARAM_CLASS_ANGLE_BRACKET_COLON:
                                lbracket = "<:";
                                rbracket = ":>";
                                break;
                            case (int)FunctionData.ParamClassEnum.PARAM_CLASS_BRACE_PERCENT:
                                lbracket = "{%";
                                rbracket = "%}";
                                break;
                            case (int)FunctionData.ParamClassEnum.PARAM_CLASS_BRACKET_PERCENT:
                                lbracket = "[%";
                                rbracket = "%]";
                                break;
                            case (int)FunctionData.ParamClassEnum.PARAM_CLASS_PARENTHESIS_PERCENT:
                                lbracket = "(%";
                                rbracket = "%)";
                                break;
                            case (int)FunctionData.ParamClassEnum.PARAM_CLASS_ANGLE_BRACKET_PERCENT:
                                lbracket = "<%";
                                rbracket = "%>";
                                break;
                            case (int)FunctionData.ParamClassEnum.PARAM_CLASS_PERIOD_STAR:
                                lbracket = ".*";
                                rbracket = string.Empty;
                                break;
                            case (int)FunctionData.ParamClassEnum.PARAM_CLASS_QUESTION_PERIOD_STAR:
                                lbracket = "?.*";
                                rbracket = string.Empty;
                                break;
                            case (int)FunctionData.ParamClassEnum.PARAM_CLASS_POINTER_STAR:
                                lbracket = "->*";
                                rbracket = string.Empty;
                                break;
                        }
                        stream.Append(lbracket);
                        int ct = data.GetParamNum();
                        char sep = ' ';
                        for (int i = 0; i < ct; ++i) {
                            if (i > 0) {
                                stream.Append(sep);
                                stream.Append(' ');
                            }
                            ISyntaxComponent param = data.GetParam(i);
                            sep = param.GetSepChar();
                            if ((int)FunctionData.ParamClassEnum.PARAM_CLASS_PERIOD == paramClass
                                 || (int)FunctionData.ParamClassEnum.PARAM_CLASS_QUESTION_PERIOD == paramClass
                                 || (int)FunctionData.ParamClassEnum.PARAM_CLASS_POINTER == paramClass
                                 || (int)FunctionData.ParamClassEnum.PARAM_CLASS_PERIOD_STAR == paramClass
                                 || (int)FunctionData.ParamClassEnum.PARAM_CLASS_QUESTION_PERIOD_STAR == paramClass
                                 || (int)FunctionData.ParamClassEnum.PARAM_CLASS_POINTER_STAR == paramClass)
                                stream.Append(param.ToScriptString(true));
                            else
                                writeSyntaxComponent(stream, param, indent, true, false, delim);
                        }
                        stream.Append(rbracket);
                    }
                }
            }
            else {
                if (data.IsHighOrder) {
                    writeFunctionData(stream, data.LowerOrderFunction, indent, firstLineNoIndent, false, delim);
                }
                else if (data.HaveId()) {
                    string line = quoteString(data.GetId(), data.GetIdType(), delim.StringBeginDelimiter, delim.StringEndDelimiter);
                    writeText(stream, line, firstLineNoIndent ? 0 : indent);
                }
            }
            if (isLastOfStatement)
                stream.Append(data.GetSepChar());
            foreach (string cmt in data.Comments) {
                writeText(stream, cmt, 1);
            }
            writeLastComments(stream, data, indent, isLastOfStatement);
#endif
        }

        public static void writeStatementData(StringBuilder stream, StatementData data, int indent, bool firstLineNoIndent, bool isLastOfStatement, DelimiterInfo delim)
        {
#if FULL_VERSION
            writeFirstComments(stream, data, indent, firstLineNoIndent);
            FunctionData tempData = data.First.AsFunction;
            FunctionData callData = null;
            if (null != tempData) {
                callData = tempData.LowerOrderFunction;
            }
            if (null != callData && tempData.IsTernaryOperatorParamClass()) {
                //三目运算符表示为op1(cond)(true_val)op2(false_val)
                if (callData.HaveId() && callData.HaveParamOrStatement()) {
                    string line = "/*[?:]*/";                    
                    if (data.Functions.Count == 2) {
                        FunctionData funcData = data.Functions[1].AsFunction;
                        if (null != funcData && funcData.HaveId() && funcData.HaveParamOrStatement()) {
                            line = string.Format("{0} {1} {2}", callData.GetParam(0).ToScriptString(true), callData.GetId(), tempData.GetParam(0).ToScriptString(true));
                            line = string.Format("{0} {1} {2}", line, funcData.GetId(), funcData.GetParam(0).ToScriptString(true));
                        }
                    }
                    writeText(stream, line, firstLineNoIndent ? 0 : indent);
                }
            }
            else {
                int ct = data.Functions.Count;
                bool lastFuncNoParam = false;
                bool lastFuncNoStatement = false;
                for (int i = 0; i < ct; ++i) {
                    var dof = data.Functions[i];
                    ValueData val = dof.AsValue;
                    if (null != val) {
                        bool noIndent = false;
                        if (i > 0) {
                            if (lastFuncNoParam && lastFuncNoStatement) {
                                writeText(stream, " ", 0);
                                noIndent = true;
                            }
                            else if (lastFuncNoStatement) {
                                noIndent = true;
                            }
                            else {
                                writeLine(stream, string.Empty, 0);
                                noIndent = false;
                            }
                        }
                        writeValueData(stream, val, indent, firstLineNoIndent && i == 0 || noIndent, false);
                        lastFuncNoParam = true;
                        lastFuncNoStatement = true;
                    }
                    else {
                        FunctionData func = dof.AsFunction;
                        bool funcNoParam = !func.IsHighOrder && (!func.HaveParam() || func.IsMemberParamClass());
                        bool funcNoStatement = !func.HaveStatement() && !func.HaveExternScript();
                        bool noIndent = false;
                        if (i > 0) {
                            if (lastFuncNoParam && lastFuncNoStatement) {
                                writeText(stream, " ", 0);
                                noIndent = true;
                            }
                            else if (lastFuncNoStatement && funcNoStatement) {
                                noIndent = true;
                            }
                            else {
                                writeLine(stream, string.Empty, 0);
                                noIndent = false;
                            }
                        }
                        writeFunctionData(stream, func, indent, firstLineNoIndent && i == 0 || noIndent, false, delim);
                        lastFuncNoParam = funcNoParam;
                        lastFuncNoStatement = funcNoStatement;
                    }
                }
            }
            if (isLastOfStatement)
                stream.Append(data.GetSepChar());
            writeLastComments(stream, data, indent, isLastOfStatement);
#endif
        }
        
        internal static bool needQuote(string str)
        {
            const string escapeChars = " \t\r\n{}()[],;~`!%^&*-+=|:<>?/#\\'\"";
            if (str.Length == 0) {
                return true;
            }
            bool haveDot = false;
            bool notNum = false;
            for (int i = 0; i < str.Length; ++i) {
                char c = str[i];
                if (escapeChars.IndexOf(c) >= 0) {
                    return true;
                }
                if (c == '.') {
                    haveDot = true;
                }
                else if (!notNum && !char.IsDigit(c)) {
                    notNum = true;
                }
                if (haveDot && notNum) {
                    return true;
                }
            }
            return false;
        }

        internal static string quoteStringWithStrDefDelim(string str, int _Type)
        {
            return quoteString(str, _Type, "\"", "\"");
        }
        internal static string quoteString(string str, int _Type, string strBeginDelim, string strEndDelim)
        {
            switch (_Type) {
                case AbstractSyntaxComponent.STRING_TOKEN: {
                        return quoteString(str, strBeginDelim, strEndDelim);
                    }
                case AbstractSyntaxComponent.NUM_TOKEN:
                case AbstractSyntaxComponent.ID_TOKEN:
                    return str;
                default:
                    return str;
            }
        }
        private static string quoteString(string str, string strBeginDelim, string strEndDelim)
        {
            var sb = new StringBuilder();
            sb.Append(strBeginDelim);
            for (int i = 0; i < str.Length; i++) {
                char c = str[i];
                switch (c) {
                    case '\\':
                        sb.Append("\\\\");
                        break;
                    case '"':
                        sb.Append("\\\"");
                        break;
                    case '\'':
                        sb.Append("\\\'");
                        break;
                    case '\0':
                        sb.Append("\\\0");
                        break;
                    default:
                        sb.Append(c);
                        break;
                }
            }
            sb.Append(strEndDelim);
            return sb.ToString();
        }

        internal static string getFunctionStringWithStrDefDelim(FunctionData data, bool includeComment)
        {
            return getFunctionString(data, includeComment, "\"", "\"");
        }
        internal static string getFunctionString(FunctionData data, bool includeComment, string strBeginDelim, string strEndDelim)
        {
#if FULL_VERSION
            string lineNo = string.Empty;// string.Format("/* {0} */", data.GetLine());
            string line = string.Empty;
            if (data.IsHighOrder) {
                line = getFunctionString(data.LowerOrderFunction, includeComment, strBeginDelim, strEndDelim);
            }
            else if (data.HaveId()) {
                string op = data.GetId();
                if (data.HaveParamClassInfixFlag())
                    op = "`" + op;
                line = quoteString(op, data.GetIdType(), strBeginDelim, strEndDelim);
            }
            if (data.HaveParamOrStatement()) {
                if (data.IsOperatorParamClass()) {
                    switch (data.GetParamNum()) {
                        case 1:
                            return string.Format("{0} {1}", line, data.GetParam(0).ToScriptString(includeComment));
                        case 2:
                            return string.Format("{0} {1} {2}", data.GetParam(0).ToScriptString(includeComment), line, data.GetParam(1).ToScriptString(includeComment));
                        default:
                            return line;
                    }
                }
                else {
                    string lbracket = string.Empty;
                    string rbracket = string.Empty;
                    int paramClass = data.GetParamClassUnmasked();
                    switch (paramClass) {
                        case (int)FunctionData.ParamClassEnum.PARAM_CLASS_PARENTHESIS:
                            lbracket = "(";
                            rbracket = ")";
                            break;
                        case (int)FunctionData.ParamClassEnum.PARAM_CLASS_BRACKET:
                            lbracket = "[";
                            rbracket = "]";
                            break;
                        case (int)FunctionData.ParamClassEnum.PARAM_CLASS_PERIOD:
                            lbracket = ".";
                            rbracket = string.Empty;
                            break;
                        case (int)FunctionData.ParamClassEnum.PARAM_CLASS_PERIOD_PARENTHESIS:
                            lbracket = ".(";
                            rbracket = ")";
                            break;
                        case (int)FunctionData.ParamClassEnum.PARAM_CLASS_PERIOD_BRACKET:
                            lbracket = ".[";
                            rbracket = "]";
                            break;
                        case (int)FunctionData.ParamClassEnum.PARAM_CLASS_PERIOD_BRACE:
                            lbracket = ".{";
                            rbracket = "}";
                            break;
                        case (int)FunctionData.ParamClassEnum.PARAM_CLASS_COLON_COLON:
                            lbracket = "::";
                            rbracket = string.Empty;
                            break;
                        case (int)FunctionData.ParamClassEnum.PARAM_CLASS_COLON_COLON_PARENTHESIS:
                            lbracket = "::(";
                            rbracket = ")";
                            break;
                        case (int)FunctionData.ParamClassEnum.PARAM_CLASS_COLON_COLON_BRACKET:
                            lbracket = "::[";
                            rbracket = "]";
                            break;
                        case (int)FunctionData.ParamClassEnum.PARAM_CLASS_COLON_COLON_BRACE:
                            lbracket = "::{";
                            rbracket = "}";
                            break;
                        case (int)FunctionData.ParamClassEnum.PARAM_CLASS_QUESTION_PERIOD:
                            lbracket = "?.";
                            rbracket = string.Empty;
                            break;
                        case (int)FunctionData.ParamClassEnum.PARAM_CLASS_QUESTION_PARENTHESIS:
                            lbracket = "?(";
                            rbracket = ")";
                            break;
                        case (int)FunctionData.ParamClassEnum.PARAM_CLASS_QUESTION_BRACKET:
                            lbracket = "?[";
                            rbracket = "]";
                            break;
                        case (int)FunctionData.ParamClassEnum.PARAM_CLASS_QUESTION_BRACE:
                            lbracket = "?{";
                            rbracket = "}";
                            break;
                        case (int)FunctionData.ParamClassEnum.PARAM_CLASS_POINTER:
                            lbracket = "->";
                            rbracket = string.Empty;
                            break;
                        case (int)FunctionData.ParamClassEnum.PARAM_CLASS_STATEMENT:
                            lbracket = "{";
                            rbracket = "}";
                            break;
                        case (int)FunctionData.ParamClassEnum.PARAM_CLASS_EXTERN_SCRIPT:
                            lbracket = "{:";
                            rbracket = ":}";
                            break;
                        case (int)FunctionData.ParamClassEnum.PARAM_CLASS_BRACKET_COLON:
                            lbracket = "[:";
                            rbracket = ":]";
                            break;
                        case (int)FunctionData.ParamClassEnum.PARAM_CLASS_PARENTHESIS_COLON:
                            lbracket = "(:";
                            rbracket = ":)";
                            break;
                        case (int)FunctionData.ParamClassEnum.PARAM_CLASS_ANGLE_BRACKET_COLON:
                            lbracket = "<:";
                            rbracket = ":>";
                            break;
                        case (int)FunctionData.ParamClassEnum.PARAM_CLASS_BRACE_PERCENT:
                            lbracket = "{%";
                            rbracket = "%}";
                            break;
                        case (int)FunctionData.ParamClassEnum.PARAM_CLASS_BRACKET_PERCENT:
                            lbracket = "[%";
                            rbracket = "%]";
                            break;
                        case (int)FunctionData.ParamClassEnum.PARAM_CLASS_PARENTHESIS_PERCENT:
                            lbracket = "(%";
                            rbracket = "%)";
                            break;
                        case (int)FunctionData.ParamClassEnum.PARAM_CLASS_ANGLE_BRACKET_PERCENT:
                            lbracket = "<%";
                            rbracket = "%>";
                            break;
                        case (int)FunctionData.ParamClassEnum.PARAM_CLASS_PERIOD_STAR:
                            lbracket = ".*";
                            rbracket = string.Empty;
                            break;
                        case (int)FunctionData.ParamClassEnum.PARAM_CLASS_QUESTION_PERIOD_STAR:
                            lbracket = "?.*";
                            rbracket = string.Empty;
                            break;
                        case (int)FunctionData.ParamClassEnum.PARAM_CLASS_POINTER_STAR:
                            lbracket = "->*";
                            rbracket = string.Empty;
                            break;
                    }
                    StringBuilder stream = new StringBuilder();
                    stream.Append(lbracket);
                    if (paramClass == (int)FunctionData.ParamClassEnum.PARAM_CLASS_EXTERN_SCRIPT) {
                        stream.Append(data.GetParamId(0));
                    }
                    else {
                        int ct = data.GetParamNum();
                        for (int i = 0; i < ct; ++i) {
                            if (data.HaveParam() && i > 0) {
                                stream.Append(",");
                            }
                            ISyntaxComponent param = data.GetParam(i);
                            if ((int)FunctionData.ParamClassEnum.PARAM_CLASS_PERIOD == paramClass
                                 || (int)FunctionData.ParamClassEnum.PARAM_CLASS_QUESTION_PERIOD == paramClass
                                 || (int)FunctionData.ParamClassEnum.PARAM_CLASS_POINTER == paramClass
                                 || (int)FunctionData.ParamClassEnum.PARAM_CLASS_PERIOD_STAR == paramClass
                                 || (int)FunctionData.ParamClassEnum.PARAM_CLASS_QUESTION_PERIOD_STAR == paramClass
                                 || (int)FunctionData.ParamClassEnum.PARAM_CLASS_POINTER_STAR == paramClass)
                                stream.Append(param.ToScriptString(includeComment));
                            else
                                stream.Append(param.ToScriptString(includeComment));
                            if (data.HaveStatement()) {
                                stream.Append(";");
                            }
                        }
                    }
                    stream.Append(rbracket);
                    return string.Format("{0}{1}{2}", lineNo, line, stream.ToString());
                }
            }
            else {
                return string.Format("{0}{1}", lineNo, line);
            }
#else
      return string.Empty;
#endif
        }
        
        private static void writeStatementsOrExternScript(StringBuilder stream, FunctionData data, int indent, DelimiterInfo delim)
        {
#if FULL_VERSION
            if (data.HaveStatement()) {
                writeLine(stream, string.Empty, 0);
                writeLine(stream, "{", indent);
                ++indent;

                int ct = data.GetParamNum();
                for (int i = 0; i < ct; ++i) {
                    ISyntaxComponent tempData = data.GetParam(i);
                    writeSyntaxComponent(stream, tempData, indent, false, true, delim);
                }

                --indent;
                writeText(stream, "}", indent);
            }
            else if (data.HaveExternScript()) {
                writeLine(stream, string.Empty, 0);
                string script = data.GetParamId(0);
                if (script.IndexOf('\n') >= 0) {
                    writeLine(stream, delim.ScriptBeginDelimiter, indent);
                }
                else {
                    writeText(stream, delim.ScriptBeginDelimiter, indent);
                }
                stream.Append(script);
                if (script.Length > 0 && script[script.Length - 1] == '\n') {
                    writeText(stream, delim.ScriptEndDelimiter, indent);
                }
                else {
                    stream.Append(delim.ScriptEndDelimiter);
                }
            }
#endif
        }
        
        private static void writeFirstComments(StringBuilder stream, ISyntaxComponent data, int indent, bool firstLineNoIndent)
        {
#if FULL_VERSION
            AbstractSyntaxComponent syntaxComp = data as AbstractSyntaxComponent;
            bool isFirst = true;
            bool haveComments = false;
            bool newLine = false;
            foreach (string cmt in syntaxComp.FirstComments) {
                if (isFirst && !syntaxComp.FirstCommentOnNewLine) {
                    writeText(stream, cmt, firstLineNoIndent ? 0 : indent);
                }
                else {
                    writeLine(stream, cmt, isFirst && firstLineNoIndent ? 0 : indent);
                    newLine = true;
                }
                isFirst = false;
                haveComments = true;
            }
            if (haveComments && !newLine) {
                //行首注释必须要换行，否则可能会把代码注释掉
                writeLine(stream, string.Empty, 0);
            }
#endif
        }

        private static void writeLastComments(StringBuilder stream, ISyntaxComponent data, int indent, bool isLastOfStatement)
        {
#if FULL_VERSION
            AbstractSyntaxComponent syntaxComp = data as AbstractSyntaxComponent;
            bool isFirst = true;
            if (syntaxComp.LastComments.Count > 0) {
                if (syntaxComp.LastCommentOnNewLine) {
                    writeLine(stream, string.Empty, 0);
                }
                isFirst = true;
                foreach (string cmt in syntaxComp.LastComments) {
                    if (isFirst && !syntaxComp.LastCommentOnNewLine) {
                        writeText(stream, cmt, 1);
                    }
                    else {
                        writeText(stream, cmt, indent);
                    }
                    if (isLastOfStatement) {
                        writeLine(stream, string.Empty, 0);
                    }
                    isFirst = false;
                }
            }
            else if (isLastOfStatement) {
                writeLine(stream, string.Empty, 0);
            }
#endif
        }

        private static void writeText(StringBuilder stream, string line, int indent)
        {
#if FULL_VERSION
            for (int i = 0; i < indent; ++i) {
                stream.Append('\t');
            }
            stream.Append(line);
#endif
        }

        private static void writeLine(StringBuilder stream, string line, int indent)
        {
#if FULL_VERSION
            writeText(stream, line, indent);
            stream.Append("\r\n");
#endif
        }

        private static byte readByte(byte[] bytes, int curCodeIndex)
        {
            if (curCodeIndex < bytes.Length)
                return bytes[curCodeIndex];
            else
                return 0;
        }
        private static string readIdentifier(List<string> identifiers, int curIdIndex)
        {
            if (curIdIndex < identifiers.Count)
                return identifiers[curIdIndex];
            else
                return string.Empty;
        }
        private static bool isBinaryEndCode(byte endCodeStart, byte code, out int sep)
        {
            bool ret;
            if (code >= endCodeStart && code <= endCodeStart + (byte)AbstractSyntaxComponent.SEPARATOR_SEMICOLON - (byte)AbstractSyntaxComponent.SEPARATOR_NOTHING) {
                sep = code - endCodeStart + AbstractSyntaxComponent.SEPARATOR_NOTHING;
                ret = true;
            }
            else {
                sep = 0;
                ret = false;
            }
            return ret;
        }
        internal static List<ISyntaxComponent> readBinary(byte[] bytes, int start, int count, List<string> identifiers)
        {
            List<ISyntaxComponent> infos = new List<ISyntaxComponent>();
            int curCodeIndex = 0;
            int curIdIndex = 0;
            while (curCodeIndex < count) {
                while (curCodeIndex < count) {
                    byte b = bytes[start + curCodeIndex];
                    if (b == (byte)DslBinaryCode.BeginStatement || b == (byte)DslBinaryCode.BeginFunction || b == (byte)DslBinaryCode.BeginValue)
                        break;
                    ++curCodeIndex;
                }
                if (curCodeIndex < count) {
                    ISyntaxComponent info = readBinary(bytes, start, ref curCodeIndex, identifiers, ref curIdIndex);
                    if (null != info && info.IsValid()) {
                        infos.Add(info);
                    }
                }
            }
            return infos;
        }
        internal static ISyntaxComponent readBinary(byte[] bytes, int start, ref int curCodeIndex, List<string> identifiers, ref int curIdIndex)
        {
            ISyntaxComponent ret = null;
            byte code = readByte(bytes, start + curCodeIndex);
            if (code == (byte)DslBinaryCode.BeginValue) {
                ValueData data = new ValueData();
                readBinary(bytes, start, ref curCodeIndex, identifiers, ref curIdIndex, data);
                ret = data;
            }
            else if (code == (byte)DslBinaryCode.BeginFunction) {
                FunctionData data = new FunctionData();
                readBinary(bytes, start, ref curCodeIndex, identifiers, ref curIdIndex, data);
                ret = data;
            }
            else if (code == (byte)DslBinaryCode.BeginStatement) {
                StatementData data = new StatementData();
                readBinary(bytes, start, ref curCodeIndex, identifiers, ref curIdIndex, data);
                ret = data;
            }
            return ret;
        }
        internal static void readBinary(byte[] bytes, int start, ref int curCodeIndex, List<string> identifiers, ref int curIdIndex, ValueData data)
        {
            byte code = readByte(bytes, start + curCodeIndex++);
            if (code == (byte)DslBinaryCode.BeginValue) {
                code = readByte(bytes, start + curCodeIndex);
                if (code >= (byte)DslBinaryCode.ValueTypeBegin) {
                    ++curCodeIndex;
                    data.SetType(code - (byte)DslBinaryCode.ValueTypeBegin);
                    data.SetId(readIdentifier(identifiers, curIdIndex++));
                    int byteCount;
                    int v = read7BitEncodedInt(bytes, start + curCodeIndex, out byteCount);
                    data.SetLine(v);
                    curCodeIndex += byteCount;
                }
                code = readByte(bytes, start + curCodeIndex);
                int sep;
                if (isBinaryEndCode((byte)DslBinaryCode.EndValue, code, out sep)) {
                    data.SetSeparator(sep);
                    ++curCodeIndex;
                }
            }
        }
        internal static void readBinary(byte[] bytes, int start, ref int curCodeIndex, List<string> identifiers, ref int curIdIndex, FunctionData data)
        {
            byte code = readByte(bytes, start + curCodeIndex++);
            if (code == (byte)DslBinaryCode.BeginFunction) {
                code = readByte(bytes, start + curCodeIndex);
                if (code >= (byte)DslBinaryCode.ParamOrExternClassBegin) {
                    ++curCodeIndex;
                    data.SetParamClass(code - (byte)DslBinaryCode.ParamOrExternClassBegin);
                    if (data.HaveParamOrStatement()) {
                        int byteCount;
                        int v = read7BitEncodedInt(bytes, start + curCodeIndex, out byteCount);
                        curCodeIndex += byteCount;
                        data.Params.Capacity = v;
                    }
                }
                code = readByte(bytes, start + curCodeIndex);
                if (code == (byte)DslBinaryCode.BeginValue) {
                    ValueData valueData = new ValueData();
                    readBinary(bytes, start, ref curCodeIndex, identifiers, ref curIdIndex, valueData);
                    data.Name = valueData;
                }
                else if (code == (byte)DslBinaryCode.BeginFunction) {
                    FunctionData callData = new FunctionData();
                    readBinary(bytes, start, ref curCodeIndex, identifiers, ref curIdIndex, callData);
                    data.LowerOrderFunction = callData;
                }
                for (; ; ) {
                    code = readByte(bytes, start + curCodeIndex);
                    int sep;
                    if (isBinaryEndCode((byte)DslBinaryCode.EndFunction, code, out sep)) {
                        data.SetSeparator(sep);
                        ++curCodeIndex;
                        break;
                    }
                    else {
                        ISyntaxComponent syntaxData = readBinary(bytes, start, ref curCodeIndex, identifiers, ref curIdIndex);
                        if (null != syntaxData) {
                            data.Params.Add(syntaxData);
                        }
                        else {
                            break;
                        }
                    }
                }
            }
        }
        internal static void readBinary(byte[] bytes, int start, ref int curCodeIndex, List<string> identifiers, ref int curIdIndex, StatementData data)
        {
            byte code = readByte(bytes, start + curCodeIndex++);
            if (code == (byte)DslBinaryCode.BeginStatement) {
                int byteCount;
                int v = read7BitEncodedInt(bytes, start + curCodeIndex, out byteCount);
                curCodeIndex += byteCount;
                data.Functions.Capacity = v;
                for (; ; ) {
                    code = readByte(bytes, start + curCodeIndex);
                    int sep;
                    if (code == (byte)DslBinaryCode.BeginValue) {
                        ValueData valData = new ValueData();
                        readBinary(bytes, start, ref curCodeIndex, identifiers, ref curIdIndex, valData);
                        data.Functions.Add(valData);
                    }
                    else if (code == (byte)DslBinaryCode.BeginFunction) {
                        FunctionData funcData = new FunctionData();
                        readBinary(bytes, start, ref curCodeIndex, identifiers, ref curIdIndex, funcData);
                        data.Functions.Add(funcData);
                    }
                    else if (isBinaryEndCode((byte)DslBinaryCode.EndStatement, code, out sep)) {
                        data.SetSeparator(sep);
                        ++curCodeIndex;
                        break;
                    }
                    else {
                        break;
                    }
                }
            }
        }
        //---------------------------------------------------------------------------------------------
#if FULL_VERSION
        private static byte getBinaryEndCode(byte endCode, int sep)
        {
            if (sep >= AbstractSyntaxComponent.SEPARATOR_NOTHING && sep <= AbstractSyntaxComponent.SEPARATOR_SEMICOLON) {
                return (byte)(endCode + sep - AbstractSyntaxComponent.SEPARATOR_NOTHING);
            }
            else {
                return endCode;
            }
        }
        internal static void writeBinary(MemoryStream stream, List<string> identifiers, ISyntaxComponent data)
        {
            ValueData val = data as ValueData;
            if (null != val) {
                writeBinary(stream, identifiers, val);
            }
            else {
                FunctionData call = data as FunctionData;
                if (null != call) {
                    writeBinary(stream, identifiers, call);
                }
                else {
                    StatementData statement = data as StatementData;
                    writeBinary(stream, identifiers, statement);
                }
            }
        }
        internal static void writeBinary(MemoryStream stream, List<string> identifiers, ValueData data)
        {
            stream.WriteByte((byte)DslBinaryCode.BeginValue);
            if (null != data) {
                stream.WriteByte((byte)((int)DslBinaryCode.ValueTypeBegin + data.GetIdType()));
                identifiers.Add(data.GetId());
                write7BitEncodedInt(stream, data.GetLine());
            }
            stream.WriteByte(getBinaryEndCode((byte)DslBinaryCode.EndValue, data.GetSeparator()));
        }
        internal static void writeBinary(MemoryStream stream, List<string> identifiers, FunctionData data)
        {
            stream.WriteByte((byte)DslBinaryCode.BeginFunction);
            if (null != data) {
                stream.WriteByte((byte)((int)DslBinaryCode.ParamOrExternClassBegin + data.GetParamClass()));
                if (data.HaveParamOrStatement()) {
                    write7BitEncodedInt(stream, data.GetParamNum());
                }
                if (data.IsHighOrder) {
                    writeBinary(stream, identifiers, data.LowerOrderFunction);
                }
                else {
                    writeBinary(stream, identifiers, data.Name);
                }
                foreach (ISyntaxComponent syntaxData in data.Params) {
                    writeBinary(stream, identifiers, syntaxData);
                }
            }
            stream.WriteByte(getBinaryEndCode((byte)DslBinaryCode.EndFunction, data.GetSeparator()));
        }
        internal static void writeBinary(MemoryStream stream, List<string> identifiers, StatementData data)
        {
            stream.WriteByte((byte)DslBinaryCode.BeginStatement);
            write7BitEncodedInt(stream, data.GetFunctionNum());
            foreach (var f in data.Functions) {
                var val = f.AsValue;
                if (null != val) {
                    writeBinary(stream, identifiers, val);
                }
                else {
                    var func = f.AsFunction;
                    writeBinary(stream, identifiers, func);
                }
            }
            stream.WriteByte(getBinaryEndCode((byte)DslBinaryCode.EndStatement, data.GetSeparator()));
        }
#endif
    }

    internal class CppParseTableChecker : Dsl.Common.IVisitor
    {
        public void Visit(short[] production, int[] production_row, short[] parse, int[] parse_row, short start_symbol, short start_action)
        {
            for (short sym = start_symbol; sym < start_action; ++sym) {
                for (short tok = 1; tok < start_symbol; ++tok) {
                    short entry, lhs;
                    int index;
                    index = parse_row[sym - (start_symbol - 1)];
                    index += tok;
                    entry = parse[index];
                    if (entry <= 0) {
                        m_StringBuilder.AppendFormat("Error for symbol {0} token {1}", Dsl.Parser.CppString.GetSymbolName(sym), Dsl.Parser.CppString.GetSymbolName(tok));
                    }
                    else {
                        index = production_row[entry];
                        lhs = production[index + 1];
                        if (lhs != sym) {
                            m_StringBuilder.AppendFormat("Error for symbol {0} token {1} lhs {2} production {3}", Dsl.Parser.CppString.GetSymbolName(sym), Dsl.Parser.CppString.GetSymbolName(tok), Dsl.Parser.CppString.GetSymbolName(lhs), Dsl.Parser.CppString.GetProductionName(entry));
                        }
                        else {
                            m_StringBuilder.AppendFormat("Success for symbol {0} token {1} production {2}", Dsl.Parser.CppString.GetSymbolName(sym), Dsl.Parser.CppString.GetSymbolName(tok), Dsl.Parser.CppString.GetProductionName(entry));
                        }
                    }
                    m_StringBuilder.AppendLine();
                }
            }
        }
        public string GetResults()
        {
            return m_StringBuilder.ToString();
        }

        private StringBuilder m_StringBuilder = new StringBuilder();
    }
}
