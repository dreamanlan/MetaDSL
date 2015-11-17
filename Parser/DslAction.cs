using System;
using System.Collections.Generic;
using System.Text;

namespace Dsl.Parser
{
  abstract class DslAction
  {
    internal abstract void predict(short production_number);
    internal abstract void execute(int number);
  }
  delegate string GetLastTokenDelegation();
  delegate int GetLastLineNumberDelegation();
  class RuntimeAction : DslAction
  {
    class SemanticInfo
    {
      internal string token;
      internal int value;

      internal SemanticInfo()
      { }
      internal SemanticInfo(string _token, int _value)
      {
        token = _token;
        value = _value;
      }
    };

    internal RuntimeAction(List<DslInfo> datas)
    {
      mScriptDatas = datas;
    }

    internal GetLastTokenDelegation onGetLastToken
    {
      get { return mGetLastToken; }
      set { mGetLastToken = value; }
    }
    internal GetLastLineNumberDelegation onGetLastLineNumber
    {
      get { return mGetLastLineNumber; }
      set { mGetLastLineNumber = value; }
    }

    internal override void predict(short production_number)
    {
#if FULL_VERSION
      //LogSystem.Info("{0}", DslString.GetProductionName(production_number));
#endif
    }
    internal override void execute(int number)
    {
      switch (number) {
        case 1: endStatement(); break;
        case 2: pushId(); break;
        case 3: buildOperator(); break;
        case 4: buildFirstTernaryOperator(); break;
        case 5: buildSecondTernaryOperator(); break;
        case 6: beginStatement(); break;
        case 7: beginFunction(); break;
        case 8: endFunction(); break;
        case 9: setFunctionId(); break;
        case 10: markHaveStatement(); break;
        case 11: markHaveExternScript(); break;
        case 12: setExternScript(); break;
        case 13: markParenthesisParam(); break;
        case 14: buildHighOrderFunction(); break;
        case 15: markBracketParam(); break;
        case 16: markPeriodParam(); break;
        case 17: setMemberId(); break;
        case 18: markPeriodParenthesisParam(); break;
        case 19: markPeriodBracketParam(); break;
        case 20: markPeriodBraceParam(); break;
        case 21: pushStr(); break;
        case 22: pushNum(); break;
        case 23: pushTrue(); break;
        case 24: pushFalse(); break;
      }
    }

    internal void buildOperator()
    {
      int type;
      string name = pop(out type);

      StatementData arg = getCurStatement();
      popStatement();

      StatementData _statement = newStatement();
      FunctionData first = _statement.First;
      first.Call.Name.SetLine(getLastLineNumber());
      mStatementSemanticStack.Push(_statement);

      StatementData statement = getCurStatement();
      FunctionData func = getLastFunction();
      if (!func.IsValid()) {
        func.Call.SetParamClass((int)CallData.ParamClassEnum.PARAM_CLASS_OPERATOR);

        func.Call.Name.SetId(name);
        func.Call.Name.SetType(type);

        if (arg.IsValid()) {
          func.Call.AddParams(arg);
        }
      }
    }
    internal void buildFirstTernaryOperator()
    {
      int type;
      string name = pop(out type);

      StatementData arg = popStatement();

      StatementData _statement = newStatement();
      FunctionData first = _statement.First;
      first.Call.Name.SetLine(getLastLineNumber());
      mStatementSemanticStack.Push(_statement);

      StatementData statement = getCurStatement();
      FunctionData func = getLastFunction();
      if (!func.IsValid()) {
        func.Call.SetParamClass((int)CallData.ParamClassEnum.PARAM_CLASS_TERNARY_OPERATOR);
        func.SetExtentClass((int)FunctionData.ExtentClassEnum.EXTENT_CLASS_STATEMENT);

        func.Call.Name.SetId(name);
        func.Call.Name.SetType(type);

        if (arg.IsValid()) {
          func.Call.AddParams(arg);
        }
      }
    }
    internal void buildSecondTernaryOperator()
    {
      int type;
      string name = pop(out type);

      StatementData statement = getCurStatement();
      FunctionData newFunc = new FunctionData();
      statement.Functions.Add(newFunc);

      FunctionData func = getLastFunction();
      if (!func.IsValid()) {
        func.Call.SetParamClass((int)CallData.ParamClassEnum.PARAM_CLASS_TERNARY_OPERATOR);
        func.SetExtentClass((int)FunctionData.ExtentClassEnum.EXTENT_CLASS_STATEMENT);

        func.Call.Name.SetId(name);
        func.Call.Name.SetType(type);
      }
    }
    internal void beginStatement()
    {
      StatementData statement = newStatement();
      FunctionData first = statement.First;
      first.Call.Name.SetLine(getLastLineNumber());
      mStatementSemanticStack.Push(statement);
    }
    internal void endStatement()
    {
      StatementData statement = popStatement();
      if (mStatementSemanticStack.Count == 0) {
        simplifyStatementData(statement);
        if (!statement.IsValid()) {
          //_epsilon_表达式无语句语义
          return;
        }
        //顶层元素结束
        DslInfo scriptData = new DslInfo();
        scriptData.CopyFrom(statement);
        scriptData.SetLoaded(true);
        mScriptDatas.Add(scriptData);
      } else {
        ISyntaxComponent statementSyntax = simplifyStatement(statement);

        FunctionData func = getLastFunction();
        switch (func.GetExtentClass()) {
          case (int)FunctionData.ExtentClassEnum.EXTENT_CLASS_NOTHING: {
              /*这段先暂时注掉，忘记原来为啥要允许空语句作函数参数了(现在对于明确的空串参数不会判断为无效语句了)
              if(func.Call.getParamClass()==(int)CallData.ParamClassEnum.PARAM_CLASS_OPERATOR && !statement.IsValid())
                return;//操作符就不支持空语句作参数了
              //函数参数，允许空语句，用于表达默认状态(副作用是a()与a[]将总是会有一个空语句参数)。
              */
              if (statement.IsValid())
                func.Call.AddParams(statementSyntax);
            }
            break;
          case (int)FunctionData.ExtentClassEnum.EXTENT_CLASS_STATEMENT: {
              if (!statement.IsValid()) {
                //_epsilon_表达式无语句语义
                return;
              }
              //函数扩展语句部分
              func.AddStatement(statementSyntax);
            }
            break;
        }
      }
    }
    internal void beginFunction()
    {
      StatementData statement = getCurStatement();
      FunctionData func = getLastFunction();
      if (func.IsValid()) {
        //语句的多元函数的其它元函数名
        FunctionData newFunc = new FunctionData();
        CallData call = new CallData();
        ValueData name = new ValueData();
        call.Name = name;
        newFunc.Call = call;
        statement.Functions.Add(newFunc);
      }
    }
    internal void setFunctionId()
    {
      int type;
      string name = pop(out type);
      FunctionData func = getLastFunction();
      if (!func.IsValid()) {
        func.Call.Name.SetId(name);
        func.Call.Name.SetType(type);
      }
    }
    internal void setMemberId()
    {
      int type;
      string name = pop(out type);
      if (type == CallData.ID_TOKEN)
        type = CallData.STRING_TOKEN;
      FunctionData func = getLastFunction();
      if (!func.IsValid()) {
        func.Call.Name.SetId(name);
        func.Call.Name.SetType(type);
      }
    }
    internal void endFunction()
    {

    }
    internal void buildHighOrderFunction()
    {
      //高阶函数构造（当前函数返回一个函数）
      FunctionData func = getLastFunction();
      CallData temp = new CallData();
      temp.Call = func.Call;
      func.Clear();
      func.Call = temp;
    }
    internal void markParenthesisParam()
    {
      FunctionData func = getLastFunction();
      func.Call.SetParamClass((int)CallData.ParamClassEnum.PARAM_CLASS_PARENTHESIS);
    }
    internal void markBracketParam()
    {
      FunctionData func = getLastFunction();
      func.Call.SetParamClass((int)CallData.ParamClassEnum.PARAM_CLASS_BRACKET);
    }
    internal void markPeriodParam()
    {
      FunctionData func = getLastFunction();
      func.Call.SetParamClass((int)CallData.ParamClassEnum.PARAM_CLASS_PERIOD);
    }
    internal void markPeriodParenthesisParam()
    {
      FunctionData func = getLastFunction();
      func.Call.SetParamClass((int)CallData.ParamClassEnum.PARAM_CLASS_PERIOD_PARENTHESIS);
    }
    internal void markPeriodBracketParam()
    {
      FunctionData func = getLastFunction();
      func.Call.SetParamClass((int)CallData.ParamClassEnum.PARAM_CLASS_PERIOD_BRACKET);
    }
    internal void markPeriodBraceParam()
    {
      FunctionData func = getLastFunction();
      func.Call.SetParamClass((int)CallData.ParamClassEnum.PARAM_CLASS_PERIOD_BRACE);
    }
    internal void markHaveStatement()
    {
      FunctionData func = getLastFunction();
      func.SetExtentClass((int)FunctionData.ExtentClassEnum.EXTENT_CLASS_STATEMENT);
    }
    internal void markHaveExternScript()
    {
      FunctionData func = getLastFunction();
      func.SetExtentClass((int)FunctionData.ExtentClassEnum.EXTENT_CLASS_EXTERN_SCRIPT);
    }
    internal void setExternScript()
    {
      FunctionData func = getLastFunction();
      func.SetExternScript(getLastToken());
    }
    internal void pushId()
    {
      push(getLastToken(), CallData.ID_TOKEN);
    }
    internal void pushNum()
    {
      push(getLastToken(), CallData.NUM_TOKEN);
    }
    internal void pushStr()
    {
      push(getLastToken(), CallData.STRING_TOKEN);
    }
    internal void pushTrue()
    {
      push("true", CallData.BOOL_TOKEN);
    }
    internal void pushFalse()
    {
      push("false", CallData.BOOL_TOKEN);
    }

    private void push(string s, int val)
    {
      mSemanticStack.Push(new SemanticInfo(s, val));
    }
    private string pop(out int val)
    {
      val = 0;
      if (mSemanticStack.Count == 0)
        return "null_stack_!!!";
      SemanticInfo info = mSemanticStack.Pop();
      val = info.value;
      return info.token;
    }
    private StatementData popStatement()
    {
      if (mStatementSemanticStack.Count == 0) {
        return newStatement();
      }
      StatementData cdata = mStatementSemanticStack.Pop();
      return cdata;
    }
    private StatementData getCurStatement()
    {
      if (mStatementSemanticStack.Count == 0)
        return null;
      StatementData topData = mStatementSemanticStack.Peek();
      return topData;
    }
    private FunctionData getFirstFunction()
    {
      StatementData statement = getCurStatement();
      return statement.First;
    }
    private FunctionData getSecondFunction()
    {
      StatementData statement = getCurStatement();
      return statement.Second;
    }
    private FunctionData getLastFunction()
    {
      StatementData statement = getCurStatement();
      return statement.Last;
    }
    private StatementData newStatement()
    {
      StatementData data = new StatementData();
      FunctionData func = new FunctionData();
      CallData call = new CallData();
      ValueData name = new ValueData();
      call.Name = name;
      func.Call = call;
      data.Functions.Add(func);
      return data;
    }
    private ISyntaxComponent simplifyStatement(StatementData data)
    {
      //对语句进行化简（语法分析过程中为了方便，全部按完整StatementData来构造，这里化简为原来的类型：ValueData/CallData/FunctionData等，主要涉及参数与语句部分）
      if (data.Functions.Count == 1) {
        //只有一个函数的语句退化为函数（再按函数进一步退化）。
        FunctionData func = data.Functions[0];
        return simplifyStatement(func);
      } else {
        //多个函数构成的语句不会退化，只对各个函数的参数与语句部分进行化简。
        simplifyStatementData(data);
        return data;
      }
    }
    private ISyntaxComponent simplifyStatement(FunctionData data)
    {
      if (!data.HaveStatement() && !data.HaveExternScript()) {
        //没有语句部分的函数退化为函数调用（再按函数调用进一步退化）。
        CallData call = data.Call;
        if (null != call) {
          return simplifyStatement(call);
        } else {
          //error
          return NullSyntax.Instance;
        }
      } else {
        //包含语句则不会退化，只进行化简
        simplifyFunctionData(data);
        return data;
      }
    }
    private ISyntaxComponent simplifyStatement(CallData data)
    {
      if (!data.HaveParam()) {
        //没有参数的调用退化为基本值数据
        if (data.IsHighOrder) {
          //这种情况应该不会出现
          return data;
        } else {
          return data.Name;
        }
      } else if (data.GetId() == "-" && data.GetParamNum() == 1) {
        ISyntaxComponent val = data.GetParam(0);
        ValueData temp = val as ValueData;
        if (null != temp && temp.IsNumber()) {
          return new ValueData("-" + temp.GetId(), ValueData.NUM_TOKEN);
        } else {
          simplifyCallData(data);
          return data;
        }
      } else if (data.GetId() == "+" && data.GetParamNum() == 1) {
        ISyntaxComponent val = data.GetParam(0);
        ValueData temp = val as ValueData;
        if (null != temp && temp.IsNumber()) {
          return new ValueData(temp.GetId(), ValueData.NUM_TOKEN);
        } else {
          simplifyCallData(data);
          return data;
        }
      } else {
        //有参数不会退化，对各参数进行化简
        simplifyCallData(data);
        return data;
      }
    }
    private void simplifyStatementData(StatementData data)
    {
      for (int i = 0; i < data.Functions.Count; ++i) {
        FunctionData func = data.Functions[i];
        simplifyFunctionData(func);
      }
    }
    private void simplifyFunctionData(FunctionData data)
    {
      if (null != data.Call) {
        simplifyCallData(data.Call);
      }
      if (data.HaveStatement()) {
        int ct = data.GetStatementNum();
        for (int i = 0; i < ct; ++i) {
          ISyntaxComponent temp = data.GetStatement(i);
          StatementData statement = temp as StatementData;
          if (null != statement) {
            data.SetStatement(i, simplifyStatement(statement));
          } else {
            FunctionData func = temp as FunctionData;
            if (null != func) {
              data.SetStatement(i, simplifyStatement(func));
            } else {
              CallData call = temp as CallData;
              if (null != call) {
                data.SetStatement(i, simplifyStatement(call));
              }
            }
          }
        }
      }
    }
    private void simplifyCallData(CallData data)
    {
      int ct = data.GetParamNum();
      for (int i = 0; i < ct; ++i) {
        ISyntaxComponent param = data.GetParam(i);
        StatementData statement = param as StatementData;
        if (null != statement) {
          data.SetParam(i, simplifyStatement(statement));
        } else {
          FunctionData func = param as FunctionData;
          if (null != func) {
            data.SetParam(i, simplifyStatement(func));
          } else {
            CallData call = param as CallData;
            if (null != call) {
              data.SetParam(i, simplifyStatement(call));
            }
          }
        }
      }
    }

    private string getLastToken()
    {
      if (null != mGetLastToken)
        return mGetLastToken();
      else
        return "";
    }
    private int getLastLineNumber()
    {
      if (null != mGetLastLineNumber)
        return mGetLastLineNumber();
      else
        return -1;
    }

    private GetLastTokenDelegation mGetLastToken;
    private GetLastLineNumberDelegation mGetLastLineNumber;
    private List<DslInfo> mScriptDatas;
    private Stack<SemanticInfo> mSemanticStack = new Stack<SemanticInfo>();
    private Stack<StatementData> mStatementSemanticStack = new Stack<StatementData>();
  }
}
