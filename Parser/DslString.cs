#if FULL_VERSION
// DslString.cs - generated by the SLK parser generator 

namespace Dsl.Parser {

class DslString {

private static string[] Nonterminal_name ={"0"

,"PROGRAM"
,"STATEMENTS"
,"STATEMENT"
,"OPERATOR_STATEMENT_1"
,"OPERATOR_STATEMENT_2"
,"OPERATOR_STATEMENT_3"
,"OPERATOR_STATEMENT_4"
,"OPERATOR_STATEMENT_5"
,"OPERATOR_STATEMENT_6"
,"OPERATOR_STATEMENT_7"
,"OPERATOR_STATEMENT_8"
,"OPERATOR_STATEMENT_9"
,"OPERATOR_STATEMENT_10"
,"OPERATOR_STATEMENT_11"
,"OPERATOR_STATEMENT_12"
,"OPERATOR_STATEMENT_DESC_0"
,"OPERATOR_STATEMENT_DESC_1"
,"OPERATOR_STATEMENT_DESC_2"
,"OPERATOR_STATEMENT_DESC_3"
,"OPERATOR_STATEMENT_DESC_4"
,"OPERATOR_STATEMENT_DESC_5"
,"OPERATOR_STATEMENT_DESC_6"
,"OPERATOR_STATEMENT_DESC_7"
,"OPERATOR_STATEMENT_DESC_8"
,"OPERATOR_STATEMENT_DESC_9"
,"OPERATOR_STATEMENT_DESC_10"
,"OPERATOR_STATEMENT_DESC_11"
,"OPERATOR_STATEMENT_DESC_12"
,"FUNCTION_STATEMENT"
,"FUNCTION_STATEMENT_DESC"
,"FUNCTION_CALLS"
,"FUNCTION_EX_CALL"
,"FUNCTION_EX_CALL_SPECIAL"
,"FUNCTION_EX"
,"FUNCTION_PARAMS"
,"MEMBER_DESC"
,"FUNCTION_ID"
,"SEP"
,"SEP_STATEMENT_*"
,"OP_TOKEN_0_OPERATOR_STATEMENT_1_*"
,"OP_TOKEN_1_OPERATOR_STATEMENT_2_OP_TOKEN_1_OPERATOR_STATEMENT_2_*"
,"OP_TOKEN_2_OPERATOR_STATEMENT_3_*"
,"OP_TOKEN_3_OPERATOR_STATEMENT_4_*"
,"OP_TOKEN_4_OPERATOR_STATEMENT_5_*"
,"OP_TOKEN_5_OPERATOR_STATEMENT_6_*"
,"OP_TOKEN_6_OPERATOR_STATEMENT_7_*"
,"OP_TOKEN_7_OPERATOR_STATEMENT_8_*"
,"OP_TOKEN_8_OPERATOR_STATEMENT_9_*"
,"OP_TOKEN_9_OPERATOR_STATEMENT_10_*"
,"OP_TOKEN_10_OPERATOR_STATEMENT_11_*"
,"OP_TOKEN_11_OPERATOR_STATEMENT_12_*"
,"OP_TOKEN_12_FUNCTION_STATEMENT_*"
,"FUNCTION_EX_CALL_*"
,"FUNCTION_PARAMS_opt"
,"FUNCTION_EX_opt"
,"FUNCTION_EX_2_opt"
,"FUNCTION_PARAMS_2_opt"
,"FUNCTION_PARAMS_3_opt"
,"FUNCTION_PARAMS_4_opt"
};

private static string[] Terminal_name ={"0"

,"OP_TOKEN_0"
,"OP_TOKEN_1"
,"OP_TOKEN_2"
,"OP_TOKEN_3"
,"OP_TOKEN_4"
,"OP_TOKEN_5"
,"OP_TOKEN_6"
,"OP_TOKEN_7"
,"OP_TOKEN_8"
,"OP_TOKEN_9"
,"OP_TOKEN_10"
,"OP_TOKEN_11"
,"OP_TOKEN_12"
,"{"
,"}"
,"SCRIPT_CONTENT"
,"("
,")"
,"["
,"]"
,"."
,"IDENTIFIER"
,"STRING"
,"NUMBER"
,"TRUE"
,"FALSE"
,","
,";"
,"END_OF_SLK_INPUT"
};

private static string[] Action_name ={"0"

,"_action_endStatement"
,"_action_pushId"
,"_action_buildOperator"
,"_action_buildFirstTernaryOperator"
,"_action_buildSecondTernaryOperator"
,"_action_beginStatement"
,"_action_beginFunction"
,"_action_endFunction"
,"_action_setFunctionId"
,"_action_markHaveStatement"
,"_action_markHaveExternScript"
,"_action_setExternScript"
,"_action_markParenthesisParam"
,"_action_buildHighOrderFunction"
,"_action_markBracketParam"
,"_action_markPeriodParam"
,"_action_setMemberId"
,"_action_markPeriodParenthesisParam"
,"_action_markPeriodBracketParam"
,"_action_markPeriodBraceParam"
,"_action_pushStr"
,"_action_pushNum"
,"_action_pushTrue"
,"_action_pushFalse"
};

private static string[] Production_name ={"0"

,"PROGRAM --> STATEMENTS"
,"STATEMENTS --> STATEMENT SEP_STATEMENT_*"
,"STATEMENT --> OPERATOR_STATEMENT_DESC_0 _action_endStatement"
,"OPERATOR_STATEMENT_1 --> OPERATOR_STATEMENT_DESC_1 _action_endStatement"
,"OPERATOR_STATEMENT_2 --> OPERATOR_STATEMENT_DESC_2 _action_endStatement"
,"OPERATOR_STATEMENT_3 --> OPERATOR_STATEMENT_DESC_3 _action_endStatement"
,"OPERATOR_STATEMENT_4 --> OPERATOR_STATEMENT_DESC_4 _action_endStatement"
,"OPERATOR_STATEMENT_5 --> OPERATOR_STATEMENT_DESC_5 _action_endStatement"
,"OPERATOR_STATEMENT_6 --> OPERATOR_STATEMENT_DESC_6 _action_endStatement"
,"OPERATOR_STATEMENT_7 --> OPERATOR_STATEMENT_DESC_7 _action_endStatement"
,"OPERATOR_STATEMENT_8 --> OPERATOR_STATEMENT_DESC_8 _action_endStatement"
,"OPERATOR_STATEMENT_9 --> OPERATOR_STATEMENT_DESC_9 _action_endStatement"
,"OPERATOR_STATEMENT_10 --> OPERATOR_STATEMENT_DESC_10 _action_endStatement"
,"OPERATOR_STATEMENT_11 --> OPERATOR_STATEMENT_DESC_11 _action_endStatement"
,"OPERATOR_STATEMENT_12 --> OPERATOR_STATEMENT_DESC_12 _action_endStatement"
,"OPERATOR_STATEMENT_DESC_0 --> OPERATOR_STATEMENT_DESC_1 OP_TOKEN_0_OPERATOR_STATEMENT_1_*"
,"OPERATOR_STATEMENT_DESC_1 --> OPERATOR_STATEMENT_DESC_2 OP_TOKEN_1_OPERATOR_STATEMENT_2_OP_TOKEN_1_OPERATOR_STATEMENT_2_*"
,"OPERATOR_STATEMENT_DESC_2 --> OPERATOR_STATEMENT_DESC_3 OP_TOKEN_2_OPERATOR_STATEMENT_3_*"
,"OPERATOR_STATEMENT_DESC_3 --> OPERATOR_STATEMENT_DESC_4 OP_TOKEN_3_OPERATOR_STATEMENT_4_*"
,"OPERATOR_STATEMENT_DESC_4 --> OPERATOR_STATEMENT_DESC_5 OP_TOKEN_4_OPERATOR_STATEMENT_5_*"
,"OPERATOR_STATEMENT_DESC_5 --> OPERATOR_STATEMENT_DESC_6 OP_TOKEN_5_OPERATOR_STATEMENT_6_*"
,"OPERATOR_STATEMENT_DESC_6 --> OPERATOR_STATEMENT_DESC_7 OP_TOKEN_6_OPERATOR_STATEMENT_7_*"
,"OPERATOR_STATEMENT_DESC_7 --> OPERATOR_STATEMENT_DESC_8 OP_TOKEN_7_OPERATOR_STATEMENT_8_*"
,"OPERATOR_STATEMENT_DESC_8 --> OPERATOR_STATEMENT_DESC_9 OP_TOKEN_8_OPERATOR_STATEMENT_9_*"
,"OPERATOR_STATEMENT_DESC_9 --> OPERATOR_STATEMENT_DESC_10 OP_TOKEN_9_OPERATOR_STATEMENT_10_*"
,"OPERATOR_STATEMENT_DESC_10 --> OPERATOR_STATEMENT_DESC_11 OP_TOKEN_10_OPERATOR_STATEMENT_11_*"
,"OPERATOR_STATEMENT_DESC_11 --> OPERATOR_STATEMENT_DESC_12 OP_TOKEN_11_OPERATOR_STATEMENT_12_*"
,"OPERATOR_STATEMENT_DESC_12 --> FUNCTION_STATEMENT_DESC OP_TOKEN_12_FUNCTION_STATEMENT_*"
,"FUNCTION_STATEMENT --> FUNCTION_STATEMENT_DESC _action_endStatement"
,"FUNCTION_STATEMENT_DESC --> _action_beginStatement FUNCTION_CALLS"
,"FUNCTION_CALLS --> FUNCTION_EX_CALL_*"
,"FUNCTION_CALLS --> _action_beginFunction FUNCTION_EX_CALL_SPECIAL _action_endFunction"
,"FUNCTION_EX_CALL --> FUNCTION_ID _action_setFunctionId FUNCTION_PARAMS_opt FUNCTION_EX_opt"
,"FUNCTION_EX_CALL_SPECIAL --> FUNCTION_PARAMS FUNCTION_EX_2_opt"
,"FUNCTION_EX_CALL_SPECIAL --> FUNCTION_EX"
,"FUNCTION_EX --> { _action_markHaveStatement STATEMENTS }"
,"FUNCTION_EX --> _action_markHaveExternScript SCRIPT_CONTENT _action_setExternScript"
,"FUNCTION_PARAMS --> ( _action_markParenthesisParam STATEMENTS ) FUNCTION_PARAMS_2_opt"
,"FUNCTION_PARAMS --> [ _action_markBracketParam STATEMENTS ] FUNCTION_PARAMS_3_opt"
,"FUNCTION_PARAMS --> . MEMBER_DESC FUNCTION_PARAMS_4_opt"
,"MEMBER_DESC --> _action_markPeriodParam _action_beginStatement _action_beginFunction FUNCTION_ID _action_setMemberId _action_endFunction _action_endStatement"
,"MEMBER_DESC --> ( _action_markPeriodParenthesisParam STATEMENTS )"
,"MEMBER_DESC --> [ _action_markPeriodBracketParam STATEMENTS ]"
,"MEMBER_DESC --> { _action_markPeriodBraceParam STATEMENTS }"
,"FUNCTION_ID --> IDENTIFIER _action_pushId"
,"FUNCTION_ID --> STRING _action_pushStr"
,"FUNCTION_ID --> NUMBER _action_pushNum"
,"FUNCTION_ID --> TRUE _action_pushTrue"
,"FUNCTION_ID --> FALSE _action_pushFalse"
,"SEP --> ,"
,"SEP --> ;"
,"SEP_STATEMENT_* --> SEP STATEMENT SEP_STATEMENT_*"
,"SEP_STATEMENT_* -->"
,"OP_TOKEN_0_OPERATOR_STATEMENT_1_* --> OP_TOKEN_0 _action_pushId _action_buildOperator OPERATOR_STATEMENT_1 OP_TOKEN_0_OPERATOR_STATEMENT_1_*"
,"OP_TOKEN_0_OPERATOR_STATEMENT_1_* -->"
,"OP_TOKEN_1_OPERATOR_STATEMENT_2_OP_TOKEN_1_OPERATOR_STATEMENT_2_* --> OP_TOKEN_1 _action_pushId _action_buildFirstTernaryOperator OPERATOR_STATEMENT_2 OP_TOKEN_1 _action_pushId _action_buildSecondTernaryOperator OPERATOR_STATEMENT_2 OP_TOKEN_1_OPERATOR_STATEMENT_2_OP_TOKEN_1_OPERATOR_STATEMENT_2_*"
,"OP_TOKEN_1_OPERATOR_STATEMENT_2_OP_TOKEN_1_OPERATOR_STATEMENT_2_* -->"
,"OP_TOKEN_2_OPERATOR_STATEMENT_3_* --> OP_TOKEN_2 _action_pushId _action_buildOperator OPERATOR_STATEMENT_3 OP_TOKEN_2_OPERATOR_STATEMENT_3_*"
,"OP_TOKEN_2_OPERATOR_STATEMENT_3_* -->"
,"OP_TOKEN_3_OPERATOR_STATEMENT_4_* --> OP_TOKEN_3 _action_pushId _action_buildOperator OPERATOR_STATEMENT_4 OP_TOKEN_3_OPERATOR_STATEMENT_4_*"
,"OP_TOKEN_3_OPERATOR_STATEMENT_4_* -->"
,"OP_TOKEN_4_OPERATOR_STATEMENT_5_* --> OP_TOKEN_4 _action_pushId _action_buildOperator OPERATOR_STATEMENT_5 OP_TOKEN_4_OPERATOR_STATEMENT_5_*"
,"OP_TOKEN_4_OPERATOR_STATEMENT_5_* -->"
,"OP_TOKEN_5_OPERATOR_STATEMENT_6_* --> OP_TOKEN_5 _action_pushId _action_buildOperator OPERATOR_STATEMENT_6 OP_TOKEN_5_OPERATOR_STATEMENT_6_*"
,"OP_TOKEN_5_OPERATOR_STATEMENT_6_* -->"
,"OP_TOKEN_6_OPERATOR_STATEMENT_7_* --> OP_TOKEN_6 _action_pushId _action_buildOperator OPERATOR_STATEMENT_7 OP_TOKEN_6_OPERATOR_STATEMENT_7_*"
,"OP_TOKEN_6_OPERATOR_STATEMENT_7_* -->"
,"OP_TOKEN_7_OPERATOR_STATEMENT_8_* --> OP_TOKEN_7 _action_pushId _action_buildOperator OPERATOR_STATEMENT_8 OP_TOKEN_7_OPERATOR_STATEMENT_8_*"
,"OP_TOKEN_7_OPERATOR_STATEMENT_8_* -->"
,"OP_TOKEN_8_OPERATOR_STATEMENT_9_* --> OP_TOKEN_8 _action_pushId _action_buildOperator OPERATOR_STATEMENT_9 OP_TOKEN_8_OPERATOR_STATEMENT_9_*"
,"OP_TOKEN_8_OPERATOR_STATEMENT_9_* -->"
,"OP_TOKEN_9_OPERATOR_STATEMENT_10_* --> OP_TOKEN_9 _action_pushId _action_buildOperator OPERATOR_STATEMENT_10 OP_TOKEN_9_OPERATOR_STATEMENT_10_*"
,"OP_TOKEN_9_OPERATOR_STATEMENT_10_* -->"
,"OP_TOKEN_10_OPERATOR_STATEMENT_11_* --> OP_TOKEN_10 _action_pushId _action_buildOperator OPERATOR_STATEMENT_11 OP_TOKEN_10_OPERATOR_STATEMENT_11_*"
,"OP_TOKEN_10_OPERATOR_STATEMENT_11_* -->"
,"OP_TOKEN_11_OPERATOR_STATEMENT_12_* --> OP_TOKEN_11 _action_pushId _action_buildOperator OPERATOR_STATEMENT_12 OP_TOKEN_11_OPERATOR_STATEMENT_12_*"
,"OP_TOKEN_11_OPERATOR_STATEMENT_12_* -->"
,"OP_TOKEN_12_FUNCTION_STATEMENT_* --> OP_TOKEN_12 _action_pushId _action_buildOperator FUNCTION_STATEMENT OP_TOKEN_12_FUNCTION_STATEMENT_*"
,"OP_TOKEN_12_FUNCTION_STATEMENT_* -->"
,"FUNCTION_EX_CALL_* --> _action_beginFunction FUNCTION_EX_CALL _action_endFunction FUNCTION_EX_CALL_*"
,"FUNCTION_EX_CALL_* -->"
,"FUNCTION_PARAMS_opt --> FUNCTION_PARAMS"
,"FUNCTION_PARAMS_opt -->"
,"FUNCTION_EX_opt --> FUNCTION_EX"
,"FUNCTION_EX_opt -->"
,"FUNCTION_EX_2_opt --> FUNCTION_EX"
,"FUNCTION_EX_2_opt -->"
,"FUNCTION_PARAMS_2_opt --> _action_buildHighOrderFunction FUNCTION_PARAMS"
,"FUNCTION_PARAMS_2_opt -->"
,"FUNCTION_PARAMS_3_opt --> _action_buildHighOrderFunction FUNCTION_PARAMS"
,"FUNCTION_PARAMS_3_opt -->"
,"FUNCTION_PARAMS_4_opt --> _action_buildHighOrderFunction FUNCTION_PARAMS"
,"FUNCTION_PARAMS_4_opt -->"
};

private const short   START_SYMBOL = 30;
private const short   START_ACTION = 89;
private const short   END_ACTION = 113;

internal static string  GetSymbolName ( short symbol )
{
  if ( symbol >= START_ACTION && symbol < END_ACTION ) {
      return ( Action_name [symbol - (START_ACTION-1)] );
  } else if ( symbol >= START_SYMBOL ) {
      return ( Nonterminal_name [symbol - (START_SYMBOL-1)] );
  } else if ( symbol > 0 ) {
      return ( Terminal_name [ symbol ] );
  }
  return ( "not a symbol" );
  }

internal static string  GetProductionName ( short production_number )
{
  return ( Production_name [production_number] );
}

};

}
#endif