//--------------------------------------------------------------------------------------
//**************************************************************************************
//**************************************************************************************
//**************************************************************************************
//--------------------------------------------------------------------------------------

#define PRINT_FUNCTION_SCRIPT_DEBUG_INFO printf

namespace Dsl
{
  template<class RealTypeT> inline
    void RuntimeBuilderT<RealTypeT>::setExternScript(void)
  {
      if (!preconditionCheck())return;
      Function* p = mData.getLastFunctionRef();
      if (0 != p) {
        char* pStr = mThis->getLastToken();
        if (0 != pStr) {
          if (mDataFile->IsDebugInfoEnable()) {
            PRINT_FUNCTION_SCRIPT_DEBUG_INFO("script:%s\n", pStr);
          }

          p->SetExternScript(pStr);
        }
      }
    }
  template<class RealTypeT> inline
    void RuntimeBuilderT<RealTypeT>::markOperator(void)
  {
      if (!preconditionCheck())return;
      Statement* pStatement = mData.getCurStatement();
      if (0 == pStatement)
        return;

      int commentOnNewLine;
      int num = mThis->getCommentNum(commentOnNewLine);
      for (int ix = 0; ix < num; ++ix) {
        char* cmt = mThis->getComment(ix);
        pStatement->AddLastComment(cmt);
        pStatement->SetLastCommentOnNewLine(commentOnNewLine);
      }
      mThis->resetComments();
    }
  template<class RealTypeT> inline
    void RuntimeBuilderT<RealTypeT>::buildOperator(void)
  {
      if (!preconditionCheck())return;
      RuntimeBuilderData::TokenInfo tokenInfo = mData.pop();
      if (TRUE != tokenInfo.IsValid())return;

      if (mDataFile->IsDebugInfoEnable()) {
        PRINT_FUNCTION_SCRIPT_DEBUG_INFO("op:%s\n", tokenInfo.mString);
      }

      Statement* pArg = mData.getCurStatement();
      if (0 == pArg)
        return;
      mData.popStatement();
      Statement* pStatement = mDataFile->AddNewStatementComponent();
      if (0 == pStatement)
        return;
      mData.pushStatement(pStatement);

      Function* p = mDataFile->AddNewFunctionComponent();
      if (0 != p) {
        Call& call = p->GetCall();
        call.SetParamClass(Call::PARAM_CLASS_OPERATOR);

        Value v = call.GetName();
        Value op(tokenInfo.mString, Value::TYPE_VARIABLE_NAME);
        op.SetLine(mThis->getLastLineNumber());
        call.SetName(op);
        if (pArg->IsValid()) {
          call.AddParam(pArg);
        }

        pStatement->AddFunction(p);
      }
    }
  template<class RealTypeT> inline
    void RuntimeBuilderT<RealTypeT>::buildFirstTernaryOperator(void)
  {
      if (!preconditionCheck())return;
      RuntimeBuilderData::TokenInfo tokenInfo = mData.pop();
      if (TRUE != tokenInfo.IsValid())return;

      if (mDataFile->IsDebugInfoEnable()) {
        PRINT_FUNCTION_SCRIPT_DEBUG_INFO("op1/2:%s\n", tokenInfo.mString);
      }

      Statement* pArg = mData.popStatement();
      if (0 == pArg)
        return;
      Statement* pStatement = mDataFile->AddNewStatementComponent();
      if (0 == pStatement)
        return;
      mData.pushStatement(pStatement);

      Function* p = mDataFile->AddNewFunctionComponent();
      if (0 != p) {
        Call& call = p->GetCall();
        call.SetParamClass(Call::PARAM_CLASS_TERNARY_OPERATOR);
        p->SetExtentClass(Function::EXTENT_CLASS_STATEMENT);

        Value op(tokenInfo.mString, Value::TYPE_VARIABLE_NAME);
        op.SetLine(mThis->getLastLineNumber());
        call.SetName(op);
        call.AddParam(pArg);

        pStatement->AddFunction(p);
      }
    }
  template<class RealTypeT> inline
    void RuntimeBuilderT<RealTypeT>::buildSecondTernaryOperator(void)
  {
      if (!preconditionCheck())return;
      RuntimeBuilderData::TokenInfo tokenInfo = mData.pop();
      if (TRUE != tokenInfo.IsValid())return;

      if (mDataFile->IsDebugInfoEnable()) {
        PRINT_FUNCTION_SCRIPT_DEBUG_INFO("op2/2:%s\n", tokenInfo.mString);
      }

      Statement* statement = mData.getCurStatement();
      if (0 != statement) {
        Function* p = mDataFile->AddNewFunctionComponent();
        if (0 != p) {
          Call& call = p->GetCall();
          call.SetParamClass(Call::PARAM_CLASS_TERNARY_OPERATOR);
          p->SetExtentClass(Function::EXTENT_CLASS_STATEMENT);

          Value op(tokenInfo.mString, Value::TYPE_VARIABLE_NAME);
          op.SetLine(mThis->getLastLineNumber());
          call.SetName(op);

          statement->AddFunction(p);
        }
      }
    }
  //--------------------------------------------------------------------------------------	
  template<class RealTypeT> inline
    void RuntimeBuilderT<RealTypeT>::beginStatement(void)
  {
      if (!preconditionCheck())return;
      Statement* p = mDataFile->AddNewStatementComponent();
      if (0 == p)
        return;

      int commentOnNewLine;
      int num = mThis->getCommentNum(commentOnNewLine);
      if (num > 0 && p->GetFirstCommentNum() > 0) {
        p->SetFirstCommentOnNewLine(commentOnNewLine);
      }
      for (int ix = 0; ix < num; ++ix) {
        char* cmt = mThis->getComment(ix);
        p->AddFirstComment(cmt);
      }
      mThis->resetComments();

      mData.pushStatement(p);
    }
  template<class RealTypeT> inline
    void RuntimeBuilderT<RealTypeT>::endStatement(void)
  {
      if (!preconditionCheck())return;
      Statement* statement = mData.popStatement();
      if (0 == statement)
        return;
      if (strcmp(statement->GetId(), "@@delimiter") == 0 && statement->GetFunctionNum() == 1 && (statement->GetLastFunctionRef()->GetCall().GetParamNum() == 1 || statement->GetLastFunctionRef()->GetCall().GetParamNum() == 3) && !statement->GetLastFunctionRef()->GetCall().IsHighOrder()) {
        const Call& call = statement->GetLastFunctionRef()->GetCall();
        const char* type = call.GetParam(0)->GetId();
        if (call.GetParamNum() == 3) {
          const char* begin = call.GetParam(1)->GetId();
          const char* end = call.GetParam(2)->GetId();
          if (strcmp(type, "string") == 0) {
            mThis->setStringDelimiter(begin, end);
          } else if (strcmp(type, "script") == 0) {
            mThis->setScriptDelimiter(begin, end);
          } else {
            //invalid
          }
        } else {
          if (strcmp(type, "string") == 0) {
            mThis->setStringDelimiter("", "");
          } else if (strcmp(type, "script") == 0) {
            mThis->setScriptDelimiter("", "");
          } else {
            //invalid
          }
        }
        return;
      }

      int commentOnNewLine;
      int num = mThis->getCommentNum(commentOnNewLine);
      if (num > 0 && statement->GetLastCommentNum() > 0) {
        statement->SetLastCommentOnNewLine(commentOnNewLine);
      }
      for (int ix = 0; ix < num; ++ix) {
        char* cmt = mThis->getComment(ix);
        statement->AddLastComment(cmt);
      }
      mThis->resetComments();

      if (mData.isSemanticStackEmpty()) {
        simplifyStatementData(*statement);
        if (!statement->IsValid()) {
          //_epsilon_���ʽ���������
          if (mDataFile->GetDslInfoNum() > 0 && statement->GetFirstCommentNum() > 0) {
            Statement* last = mDataFile->GetDslInfo(mDataFile->GetDslInfoNum() - 1);
            if (last->GetLastCommentNum() <= 0) {
              last->SetLastCommentOnNewLine(statement->IsFirstCommentOnNewLine());
            }
            int fnum = statement->GetFirstCommentNum();
            for (int ix = 0; ix < fnum; ++ix) {
              last->AddLastComment(statement->GetFirstComment(ix));
            }
          }
          return;
        }
        //����Ԫ�ؽ���
        mDataFile->AddStatement(statement);
        mThis->setCanFinish(TRUE);
      } else {
        ISyntaxComponent& statementSyntax = simplifyStatement(*statement);

        Function* p = mData.getLastFunctionRef();
        if (0 != p) {
          Call& call = p->GetCall();
          switch (p->GetExtentClass()) {
          case Function::EXTENT_CLASS_NOTHING: {
                                                 if (call.GetParamClass() == Call::PARAM_CLASS_OPERATOR && !statement->IsValid())
                                                   return;//�������Ͳ�֧�ֿղ�����

                                                 //�����������������䣬���ڱ��Ĭ��״̬(��������a()��a[]�����ǻ���һ����������)��
                                                 call.AddParam(&statementSyntax);
          }
            break;
          case Function::EXTENT_CLASS_STATEMENT: {
                                                   if (!statementSyntax.IsValid()) {
                                                     //_epsilon_���ʽ���������
                                                     if (p->GetStatementNum() > 0 && statement->GetFirstCommentNum() > 0) {
                                                       ISyntaxComponent* last = p->GetStatement(p->GetStatementNum() - 1);
                                                       if (last->GetLastCommentNum() <= 0) {
                                                         last->SetLastCommentOnNewLine(statement->IsFirstCommentOnNewLine());
                                                       }
                                                       int fnum = statement->GetFirstCommentNum();
                                                       for (int ix = 0; ix < fnum; ++ix) {
                                                         last->AddLastComment(statement->GetFirstComment(ix));
                                                       }
                                                     }
                                                     return;
                                                   }
                                                   //������չ��䲿��
                                                   p->AddStatement(&statementSyntax);
          }
            break;
          }
        }
      }
    }
  template<class RealTypeT> inline
    void RuntimeBuilderT<RealTypeT>::beginFunction(void)
  {
      if (!preconditionCheck())return;
      Statement* statement = mData.getCurStatement();
      if (0 != statement) {
        Function* newFunc = mDataFile->AddNewFunctionComponent();
        if (0 != newFunc) {
          statement->AddFunction(newFunc);
        }
      }
    }
  template<class RealTypeT> inline
    void RuntimeBuilderT<RealTypeT>::setFunctionId(void)
  {
      if (!preconditionCheck())return;
      RuntimeBuilderData::TokenInfo tokenInfo = mData.pop();
      if (TRUE != tokenInfo.IsValid())return;

      if (mDataFile->IsDebugInfoEnable()) {
        PRINT_FUNCTION_SCRIPT_DEBUG_INFO("id:%s\n", tokenInfo.mString);
      }

      Function* p = mData.getLastFunctionRef();
      if (0 != p && !p->IsValid()) {
        Value val = tokenInfo.ToValue();
        if (TRUE == val.IsValid()) {
          val.SetLine(mThis->getLastLineNumber());
          p->GetCall().SetName(val);
        }
      }
    }
  template<class RealTypeT> inline
    void RuntimeBuilderT<RealTypeT>::setMemberId(void)
  {
      if (!preconditionCheck())return;
      RuntimeBuilderData::TokenInfo tokenInfo = mData.pop();
      if (TRUE != tokenInfo.IsValid())return;

      if (mDataFile->IsDebugInfoEnable()) {
        PRINT_FUNCTION_SCRIPT_DEBUG_INFO("member:%s\n", tokenInfo.mString);
      }

      Function* p = mData.getLastFunctionRef();
      if (0 != p && !p->IsValid()) {
        Value val = tokenInfo.ToValue();
        if (TRUE == val.IsValid()) {
          val.SetLine(mThis->getLastLineNumber());
          p->GetCall().SetName(val);
        }
      }
    }
  template<class RealTypeT> inline
    void RuntimeBuilderT<RealTypeT>::endFunction(void)
  {
      if (!preconditionCheck())return;
    }
  template<class RealTypeT> inline
    void RuntimeBuilderT<RealTypeT>::buildHighOrderFunction(void)
  {
      if (!preconditionCheck())return;
      //�߽׺������죨��ǰ��������һ��������
      Function*& p = mData.getLastFunctionRef();
      if (0 == p)
        return;
      Function* newP = mDataFile->AddNewFunctionComponent();
      if (0 != newP) {
        Call& call = newP->GetCall();
        call.ClearParams();
        newP->ClearStatements();
        Value val(&p->GetCall());
        val.SetLine(p->GetLine());
        call.SetName(val);
        p = newP;
      }
    }
  template<class RealTypeT> inline
    void RuntimeBuilderT<RealTypeT>::markParenthesisParam(void)
  {
      if (!preconditionCheck())return;
      Function* p = mData.getLastFunctionRef();
      if (0 == p)
        return;
      Call& call = p->GetCall();

      int commentOnNewLine;
      int num = mThis->getCommentNum(commentOnNewLine);
      for (int ix = 0; ix < num; ++ix) {
        char* cmt = mThis->getComment(ix);
        call.AddComment(cmt);
      }
      mThis->resetComments();

      call.SetParamClass(Call::PARAM_CLASS_PARENTHESIS);
    }
  template<class RealTypeT> inline
    void RuntimeBuilderT<RealTypeT>::markBracketParam(void)
  {
      if (!preconditionCheck())return;
      Function* p = mData.getLastFunctionRef();
      if (0 == p)
        return;
      Call& call = p->GetCall();

      int commentOnNewLine;
      int num = mThis->getCommentNum(commentOnNewLine);
      for (int ix = 0; ix < num; ++ix) {
        char* cmt = mThis->getComment(ix);
        call.AddComment(cmt);
      }
      mThis->resetComments();

      call.SetParamClass(Call::PARAM_CLASS_BRACKET);
    }
  template<class RealTypeT> inline
    void RuntimeBuilderT<RealTypeT>::markPeriod(void)
  {
      if (!preconditionCheck())return;
      Function* p = mData.getLastFunctionRef();
      if (0 == p)
        return;
      Call& call = p->GetCall();

      int commentOnNewLine;
      int num = mThis->getCommentNum(commentOnNewLine);
      for (int ix = 0; ix < num; ++ix) {
        char* cmt = mThis->getComment(ix);
        call.AddComment(cmt);
      }
      mThis->resetComments();
    }
  template<class RealTypeT> inline
    void RuntimeBuilderT<RealTypeT>::markPeriodParam(void)
  {
      if (!preconditionCheck())return;
      Function* p = mData.getLastFunctionRef();
      if (0 == p)
        return;
      Call& call = p->GetCall();
      call.SetParamClass(Call::PARAM_CLASS_PERIOD);
    }
  template<class RealTypeT> inline
    void RuntimeBuilderT<RealTypeT>::markPeriodParenthesisParam(void)
  {
      if (!preconditionCheck())return;
      Function* p = mData.getLastFunctionRef();
      if (0 == p)
        return;
      Call& call = p->GetCall();
      call.SetParamClass(Call::PARAM_CLASS_PERIOD_PARENTHESIS);
    }
  template<class RealTypeT> inline
    void RuntimeBuilderT<RealTypeT>::markPeriodBracketParam(void)
  {
      if (!preconditionCheck())return;
      Function* p = mData.getLastFunctionRef();
      if (0 == p)
        return;
      Call& call = p->GetCall();
      call.SetParamClass(Call::PARAM_CLASS_PERIOD_BRACKET);
    }
  template<class RealTypeT> inline
    void RuntimeBuilderT<RealTypeT>::markPeriodBraceParam(void)
  {
      if (!preconditionCheck())return;
      Function* p = mData.getLastFunctionRef();
      if (0 == p)
        return;
      Call& call = p->GetCall();
      call.SetParamClass(Call::PARAM_CLASS_PERIOD_BRACE);
    }
  template<class RealTypeT> inline
    void RuntimeBuilderT<RealTypeT>::markHaveStatement(void)
  {
      if (!preconditionCheck())return;
      Function* p = mData.getLastFunctionRef();
      if (0 == p)
        return;
      Call& call = p->GetCall();

      int commentOnNewLine;
      int num = mThis->getCommentNum(commentOnNewLine);
      for (int ix = 0; ix < num; ++ix) {
        char* cmt = mThis->getComment(ix);
        call.AddComment(cmt);
      }
      mThis->resetComments();

      p->SetExtentClass(Function::EXTENT_CLASS_STATEMENT);
    }
  template<class RealTypeT> inline
    void RuntimeBuilderT<RealTypeT>::markHaveExternScript(void)
  {
      if (!preconditionCheck())return;
      Function* p = mData.getLastFunctionRef();
      if (0 == p)
        return;
      Call& call = p->GetCall();

      int commentOnNewLine;
      int num = mThis->getCommentNum(commentOnNewLine);
      for (int ix = 0; ix < num; ++ix) {
        char* cmt = mThis->getComment(ix);
        call.AddComment(cmt);
      }
      mThis->resetComments();

      p->SetExtentClass(Function::EXTENT_CLASS_EXTERN_SCRIPT);
    }
  template<class RealTypeT> inline
    ISyntaxComponent& RuntimeBuilderT<RealTypeT>::simplifyStatement(Statement& data)const
  {
      int num = data.GetFunctionNum();
      //�������л����﷨����������Ϊ�˷��㣬ȫ��������StatementData�����죬���ﻯ��Ϊԭ�������ͣ�ValueData/CallData/FunctionData�ȣ���Ҫ�漰��������䲿�֣�
      if (num == 1) {
        //ֻ��һ������������˻�Ϊ�������ٰ�������һ���˻�����
        Function& func = *data.GetFunction(0);
        func.CopyComments(data);
        return simplifyStatement(func);
      } else if (num == 0) {
        return NullSyntax::GetNullSyntaxRef();
      } else {
        //����������ɵ���䲻���˻���ֻ�Ը��������Ĳ�������䲿�ֽ��л���
        simplifyStatementData(data);
        return data;
      }
    }
  template<class RealTypeT> inline
    ISyntaxComponent& RuntimeBuilderT<RealTypeT>::simplifyStatement(Function& data)const
  {
      if (!data.HaveStatement() && !data.HaveExternScript()) {
        //û����䲿�ֵĺ����˻�Ϊ�������ã��ٰ��������ý�һ���˻�����
        Call& call = data.GetCall();
        if (call.IsValid()) {
          call.CopyComments(data);
          return simplifyStatement(call);
        } else {
          //error
          return NullSyntax::GetNullSyntaxRef();
        }
      } else {
        //��������򲻻��˻���ֻ���л���
        simplifyFunctionData(data);
        return data;
      }
    }
  template<class RealTypeT> inline
    ISyntaxComponent& RuntimeBuilderT<RealTypeT>::simplifyStatement(Call& data)const
  {
      if (!data.HaveParam()) {
        //û�в����ĵ����˻�Ϊ����ֵ����
        if (data.IsHighOrder()) {
          //�������Ӧ�ò������
          return data;
        } else {
          Value& name = data.GetName();
          name.CopyComments(data);
          return name;
        }
      } else if (NULL != data.GetId() && data.GetId()[0] == '-' && data.GetParamNum() == 1) {
        ISyntaxComponent& temp = *data.GetParam(0);
        if (temp.GetSyntaxType() == ISyntaxComponent::TYPE_VALUE) {
          Value& val = dynamic_cast<Value&>(temp);
          val.CopyComments(data);
          int size = (int)strlen(val.GetId()) + 1;
          char* pBuf = mDataFile->AllocString(size);
          tsnprintf(pBuf, size + 1, "-%s", val.GetId());
          if (temp.GetIdType() == Value::TYPE_FLOAT) {
            val.SetFloat(pBuf);
          } else if (temp.GetIdType()==Value::TYPE_INT) {
            val.SetInt(pBuf);
          }
          return val;
        } else {
          simplifyCallData(data);
          return data;
        }
      } else if (NULL != data.GetId() && data.GetId()[0] == '+' && data.GetParamNum() == 1) {
        ISyntaxComponent& temp = *data.GetParam(0);
        if (temp.GetSyntaxType() == ISyntaxComponent::TYPE_VALUE) {
          Value& val = dynamic_cast<Value&>(temp);
          val.CopyComments(data);
          int size = (int)strlen(val.GetId()) + 1;
          char* pBuf = mDataFile->AllocString(size);
          tsnprintf(pBuf, size + 1, "+%s", val.GetId());
          if (temp.GetIdType() == Value::TYPE_FLOAT) {
            val.SetFloat(pBuf);
          } else if (temp.GetIdType() == Value::TYPE_INT) {
            val.SetInt(pBuf);
          }
          return val;
        } else {
          simplifyCallData(data);
          return data;
        }
      } else {
        //�в��������˻����Ը��������л���
        simplifyCallData(data);
        return data;
      }
    }
  template<class RealTypeT> inline
    void RuntimeBuilderT<RealTypeT>::simplifyStatementData(Statement& data)const
  {
      for (int i = 0; i < data.GetFunctionNum(); ++i) {
        Function& func = *data.GetFunction(i);
        simplifyFunctionData(func);
      }
    }
  template<class RealTypeT> inline
    void RuntimeBuilderT<RealTypeT>::simplifyFunctionData(Function& data)const
  {
      if (data.GetCall().IsValid()) {
        simplifyCallData(data.GetCall());
      }
      if (data.HaveStatement()) {
        int ct = data.GetStatementNum();
        for (int i = 0; i < ct; ++i) {
          ISyntaxComponent& temp = *data.GetStatement(i);
          switch (temp.GetSyntaxType()) {
          case ISyntaxComponent::TYPE_STATEMENT:{
                                                  Statement& ret = dynamic_cast<Statement&>(temp);
                                                  data.SetStatement(i, &simplifyStatement(ret));
          }
            break;
          case ISyntaxComponent::TYPE_FUNCTION:{
                                                 Function& ret = dynamic_cast<Function&>(temp);
                                                 data.SetStatement(i, &simplifyStatement(ret));
          }
            break;
          case ISyntaxComponent::TYPE_CALL:{
                                             Call& ret = dynamic_cast<Call&>(temp);
                                             data.SetStatement(i, &simplifyStatement(ret));
          }
            break;
          }
        }
      }
    }
  template<class RealTypeT> inline
    void RuntimeBuilderT<RealTypeT>::simplifyCallData(Call& data)const
  {
      int ct = data.GetParamNum();
      for (int i = 0; i < ct; ++i) {
        ISyntaxComponent& temp = *data.GetParam(i);
        switch (temp.GetSyntaxType()) {
        case ISyntaxComponent::TYPE_STATEMENT:{
                                                Statement& ret = dynamic_cast<Statement&>(temp);
                                                data.SetParam(i, &simplifyStatement(ret));
        }
          break;
        case ISyntaxComponent::TYPE_FUNCTION:{
                                               Function& ret = dynamic_cast<Function&>(temp);
                                               data.SetParam(i, &simplifyStatement(ret));
        }
          break;
        case ISyntaxComponent::TYPE_CALL:{
                                           Call& ret = dynamic_cast<Call&>(temp);
                                           data.SetParam(i, &simplifyStatement(ret));
        }
          break;
        }
      }
    }
}
//--------------------------------------------------------------------------------------
//**************************************************************************************
//**************************************************************************************
//**************************************************************************************
//--------------------------------------------------------------------------------------