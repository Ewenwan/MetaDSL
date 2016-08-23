/*****************************************************************************

SlkToken.cpp

******************************************************************************/
#include "SlkParse.h"
#include "tsnprintf.h"

//mIterator,mErrorInfo�ɹ��캯�������ò������룬����Ϊ�ա�����ʹ��ʱ���ټ���Ƿ�Ϊ�ա�

static inline int myisdigit(char c, int isHex)
{
  int ret = FALSE;
  if (TRUE == isHex) {
    if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'))
      ret = TRUE;
    else
      ret = FALSE;
  } else {
    if ((c >= '0' && c <= '9'))
      ret = TRUE;
    else
      ret = FALSE;
  }
  return ret;
}

static inline int myhavelinefeed(const char* str)
{
  return strchr(str, '\n') != 0 ? 1 : 0;
}

void SlkToken::getOperatorToken(void)
{
  switch (*mIterator) {
  case '+':
  {
    pushTokenChar(*mIterator);
    ++mIterator;
    if (*mIterator == '+' || *mIterator == '=') {
      pushTokenChar(*mIterator);
      ++mIterator;
    }
  }
    break;
  case '-':
  {
    pushTokenChar(*mIterator);
    ++mIterator;
    if (*mIterator == '-' || *mIterator == '=' || *mIterator == '>') {
      pushTokenChar(*mIterator);
      ++mIterator;
    }
  }
    break;
  case '>':
  {
    pushTokenChar(*mIterator);
    ++mIterator;
    if (*mIterator == '=') {
      pushTokenChar(*mIterator);
      ++mIterator;
    } else if (*mIterator == '>') {
      pushTokenChar(*mIterator);
      ++mIterator;
      if (*mIterator == '>') {
        pushTokenChar(*mIterator);
        ++mIterator;
      }
      if (*mIterator == '=') {
        pushTokenChar(*mIterator);
        ++mIterator;
      }
    }
  }
    break;
  case '<':
  {
    pushTokenChar(*mIterator);
    ++mIterator;
    if (*mIterator == '=') {
      pushTokenChar(*mIterator);
      ++mIterator;
    } else if (*mIterator == '<') {
      pushTokenChar(*mIterator);
      ++mIterator;
      if (*mIterator == '=') {
        pushTokenChar(*mIterator);
        ++mIterator;
      }
    }
  }
    break;
  case '&':
  {
    pushTokenChar(*mIterator);
    ++mIterator;
    if (*mIterator == '=') {
      pushTokenChar(*mIterator);
      ++mIterator;
    } else if (*mIterator == '&') {
      pushTokenChar(*mIterator);
      ++mIterator;
      if (*mIterator == '=') {
        pushTokenChar(*mIterator);
        ++mIterator;
      }
    }
  }
    break;
  case '|':
  {
    pushTokenChar(*mIterator);
    ++mIterator;
    if (*mIterator == '=') {
      pushTokenChar(*mIterator);
      ++mIterator;
    } else if (*mIterator == '|') {
      pushTokenChar(*mIterator);
      ++mIterator;
      if (*mIterator == '=') {
        pushTokenChar(*mIterator);
        ++mIterator;
      }
    }
  }
    break;
  case '=':
  {
    pushTokenChar(*mIterator);
    ++mIterator;
    if (*mIterator == '=' || *mIterator == '>') {
      pushTokenChar(*mIterator);
      ++mIterator;
    }
  }
    break;
  case '!':
  case '^':
  case '*':
  case '/':
  case '%':
  {
    pushTokenChar(*mIterator);
    ++mIterator;
    if (*mIterator == '=') {
      pushTokenChar(*mIterator);
      ++mIterator;
    }
  }
    break;
  default:
  {
    pushTokenChar(*mIterator);
    ++mIterator;
  }
    break;
  }
  endToken();
}

short SlkToken::getOperatorTokenValue(void)const
{
  const char* pOperator = mCurToken;
  const char* pLastToken = mLastToken;
  int lastIsOperator = TRUE;
  if (pLastToken && pLastToken[0]) {
    if (isDelimiter(pLastToken[0])) {
      lastIsOperator = TRUE;
    } else {
      lastIsOperator = isOperator(pLastToken[0]);
    }
  }
  short val = OP_TOKEN_0_;
  if (pOperator && pOperator[0]) {
    if ((pOperator[0] == '?' || pOperator[0] == ':') && pOperator[1] == '\0') {
      val = OP_TOKEN_1_;
    } else if (pOperator[0] == '|' && pOperator[1] == '|') {
      val = OP_TOKEN_2_;
    } else if (pOperator[0] == '&' && pOperator[1] == '&') {
      val = OP_TOKEN_3_;
    } else if (pOperator[0] == '|' && pOperator[1] == '\0') {
      val = OP_TOKEN_4_;
    } else if (pOperator[0] == '^' && pOperator[1] == '\0') {
      val = OP_TOKEN_5_;
    } else if (pOperator[0] == '&' && pOperator[1] == '\0') {
      val = OP_TOKEN_6_;
    } else if ((pOperator[0] == '=' || pOperator[0] == '!') && pOperator[1] == '=') {
      val = OP_TOKEN_7_;
    } else if ((pOperator[0] == '<' || pOperator[0] == '>') && (pOperator[1] == '=' || pOperator[1] == '\0')) {
      val = OP_TOKEN_8_;
    } else if ((pOperator[0] == '<' && pOperator[1] == '<') || (pOperator[0] == '>' && pOperator[1] == '>') || (pOperator[0] == '>' && pOperator[1] == '>' && pOperator[2] == '>')) {
      val = OP_TOKEN_9_;
    } else if ((pOperator[0] == '+' || pOperator[0] == '-') && pOperator[1] == '\0') {
      if (lastIsOperator)
        val = OP_TOKEN_12_;
      else
        val = OP_TOKEN_10_;
    } else if ((pOperator[0] == '*' || pOperator[0] == '/' || pOperator[0] == '%') && pOperator[1] == '\0') {
      val = OP_TOKEN_11_;
    } else if ((pOperator[0] == '+' && pOperator[1] == '+') || (pOperator[0] == '-' && pOperator[1] == '-') || (pOperator[0] == '~' && pOperator[1] == '\0') || (pOperator[0] == '!' && pOperator[1] == '\0')) {
      val = OP_TOKEN_12_;
    } else {
      val = OP_TOKEN_0_;
    }
  }
  return val;
}

int SlkToken::isWhiteSpace(char c) const
{
  if (0 == c)
    return FALSE;
  else
    return (0 != strchr(mWhiteSpaces, c) ? TRUE : FALSE);
}

int SlkToken::isOperator(char c) const
{
  if (0 == c)
    return FALSE;
  else
    return (0 != strchr(mOperators, c) ? TRUE : FALSE);
}

int SlkToken::isDelimiter(char c) const
{
  if (0 == c)
    return FALSE;
  else
    return (0 != strchr(mDelimiters, c) ? TRUE : FALSE);
}

short SlkToken::get(void)
{
  if (NULL == mSource || NULL == mErrorAndStringBuffer) {
    return END_OF_SLK_INPUT_;
  }

  for (;;) {
    if (*mIterator == '\0') {
      if (isCanFinish()) {
        newToken();
        endTokenWithEof();
        return END_OF_SLK_INPUT_;
      } else {
        if (!mIterator.Load()) {
          newToken();
          endTokenWithEof();
          return END_OF_SLK_INPUT_;
        }
      }
    }

    int isSkip = TRUE;
    //����ע����׿ո�
    for (; isSkip && *mIterator != '\0';) {
      isSkip = FALSE;
      for (; isWhiteSpace(*mIterator); ++mIterator) {
        if (*mIterator == '\n') {
          ++mLineNumber;
          if (mCommentNum <= 0) {
            mCommentOnNewLine = TRUE;
          }
        }
        isSkip = TRUE;
      }
      //#�����ĵ���ע��
      if (*mIterator == '#') {
        newComment();
        for (; *mIterator != '\0' && *mIterator != '\n'; ++mIterator) {
          if (*mIterator != '\r')
            pushCommentChar(*mIterator);
        }
        endComment();
        isSkip = TRUE;
      }
      //C++���ĵ���ע�������ע��
      if (*mIterator == '/' && (*(mIterator + 1) == '/' || *(mIterator + 1) == '*')) {
        newComment();
        pushCommentChar(*mIterator);
        ++mIterator;
        if (*mIterator == '/') {
          pushCommentChar(*mIterator);
          ++mIterator;
          for (; *mIterator != '\0' && *mIterator != '\n'; ++mIterator) {
            if (*mIterator != '\r')
              pushCommentChar(*mIterator);
          }
          isSkip = TRUE;
        } else if (*mIterator == '*') {
          pushCommentChar(*mIterator);
          ++mIterator;
          for (;;) {
            if (*mIterator != '\0') {
              if (*mIterator == '\n') {
                pushCommentChar(*mIterator);
                ++mLineNumber;
              } else if (*mIterator == '*' && *(mIterator + 1) == '/') {
                pushCommentChar(*mIterator);
                ++mIterator;
                pushCommentChar(*mIterator);
                ++mIterator;
                break;
              } else if (*mIterator != '\r') {
                pushCommentChar(*mIterator);
              }
            } else {
              if (mIterator.Load()) {
                continue;
              } else {
                endComment();
                newToken();
                endTokenWithEof();
                return END_OF_SLK_INPUT_;
              }
            }
            ++mIterator;
          }
          isSkip = TRUE;
        }
        endComment();
      }
    }
    if (*mIterator != '\0')
      break;
  }

  newToken();
  if (isCanFinish())
    setCanFinish(FALSE);

  if (*mIterator == '{' && *(mIterator + 1) == ':') {
    ++mIterator;
    ++mIterator;
    int line = mLineNumber;
    //�����ű����� :}
    for (; *mIterator != '\0';) {
      while (*mIterator != '\0' && *mIterator != ':') {
        if (*mIterator == '\n')++mLineNumber;

        pushTokenChar(*mIterator);

        ++mIterator;
      }
      if (*mIterator == '\0')
        break;
      IScriptSource::Iterator next = mIterator + 1;
      if (*next == '}') {
        ++mIterator;
        ++mIterator;
        break;
      } else {
        pushTokenChar(*mIterator);

        ++mIterator;
      }
    }
    if (*mIterator == '\0') {
      char* pInfo = mErrorAndStringBuffer->NewErrorInfo();
      if (pInfo)
        tsnprintf(pInfo, MAX_ERROR_INFO_CAPACITY, "[line %d ]:ExternScript can't finish��", line);
    }
    endToken();
    if (myhavelinefeed(mCurToken)){
      removeFirstAndLastEmptyLine();
    }
    return SCRIPT_CONTENT_;
  } else if (isOperator(*mIterator)) {//������
    getOperatorToken();
    return getOperatorTokenValue();
  } else if (*mIterator == '.' && 0 == myisdigit(*(mIterator + 1), FALSE)) {
    char c = *mIterator;
    ++mIterator;

    pushTokenChar(c);
    endToken();
    return DOT_;
  } else if (isDelimiter(*mIterator)) {//�ָ���
    char c = *mIterator;
    ++mIterator;

    pushTokenChar(c);
    endToken();

    switch (c) {
    case '(':
      return LPAREN_;
    case ')':
      return RPAREN_;
    case '[':
      return LBRACK_;
    case ']':
      return RBRACK_;
    case '{':
      return LBRACE_;
    case '}':
      return RBRACE_;
    case ',':
      return COMMA_;
    case ';':
      return SEMI_;
    default:
      return END_OF_SLK_INPUT_;
    }
  } else {//�ؼ��֡���ʶ������
    if (*mIterator == '"' || *mIterator == '\'') {//���������������ƻ�ؼ���
      int line = mLineNumber;
      char c = *mIterator;
      for (++mIterator; *mIterator != '\0' && *mIterator != c;) {
        if (*mIterator == '\n')++mLineNumber;
        if (*mIterator == '\\') {
          //pushTokenChar(*mIterator);
          ++mIterator;
        }

        pushTokenChar(*mIterator);
        ++mIterator;

        if (*mIterator == '\0') {
          if (mIterator.Load()) {
            continue;
          } else {
            char* pInfo = mErrorAndStringBuffer->NewErrorInfo();
            if (pInfo)
              tsnprintf(pInfo, MAX_ERROR_INFO_CAPACITY, "[line %d ]:String can't finish��", line);
            endTokenWithEof();
            return END_OF_SLK_INPUT_;
          }
        }
      }
      if (*mIterator != '\0') {
        ++mIterator;
      } else {
        char* pInfo = mErrorAndStringBuffer->NewErrorInfo();
        if (pInfo)
          tsnprintf(pInfo, MAX_ERROR_INFO_CAPACITY, "[line %d ]:String can't finish��", line);
      }
      endToken();
      if (myhavelinefeed(mCurToken)){
        removeFirstAndLastEmptyLine();
      }
      return STRING_;
    } else {
      int isNum = TRUE;
      int isHex = FALSE;
      if (*mIterator == '0' && *(mIterator + 1) == 'x') {
        isHex = TRUE;
        pushTokenChar(*mIterator);
        ++mIterator;
        pushTokenChar(*mIterator);
        ++mIterator;
      }
      for (; *mIterator != '\0' && !isDelimiter(*mIterator) && !isWhiteSpace(*mIterator) && !isOperator(*mIterator); ++mIterator) {
        if (*mIterator == '#')
          break;
        else if (*mIterator == '/') {
          IScriptSource::Iterator next = mIterator + 1;
          if (*next != '\0' && (*next == '/' || *next == '*')) {
            break;
          }
        } else if (*mIterator == '.') {
          if (!isNum) {
            break;
          } else {
            IScriptSource::Iterator next = mIterator + 1;
            if (0 == myisdigit(*next, isHex)) {
              break;
            }
          }
        } else if (0 == myisdigit(*mIterator, isHex)) {
          isNum = FALSE;
        }

        pushTokenChar(*mIterator);
      }
      endToken();
      if (isNum) {
        return NUMBER_;
      } else {
        int token = handleStringOrScriptDelimiter();
        if (token)
          return token;
        return IDENTIFIER_;
      }
    }
  }
}

short SlkToken::peek(int level)
{
  short     token = 0;

  printf("peek_token is not called in an LL(1) grammar\n");

  return  token;
}

void SlkToken::setStringDelimiter(const char* begin, const char* end)
{
    tsnprintf(mStringBeginDelimiter, c_MaxDelimiterSize, "%s", begin);
    tsnprintf(mStringEndDelimiter, c_MaxDelimiterSize, "%s", end);
}

void SlkToken::setScriptDelimiter(const char* begin, const char* end)
{
    tsnprintf(mScriptBeginDelimiter, c_MaxDelimiterSize, "%s", begin);
    tsnprintf(mScriptEndDelimiter, c_MaxDelimiterSize, "%s", end);
}

int SlkToken::handleStringOrScriptDelimiter(void)
{
  if (strcmp(mCurToken, mStringBeginDelimiter) == 0){
    getBlockString(mStringEndDelimiter);
    return STRING_;
  }
  if (strcmp(mCurToken, mScriptBeginDelimiter) == 0){
    getBlockString(mScriptEndDelimiter);
    return SCRIPT_CONTENT_;
  }
  return 0;
}

void SlkToken::getBlockString(const char* delimiter)
{
  newToken();
  const char* pLeft = mIterator.GetLeft();
  const char* pFind = strstr(pLeft, delimiter);
  if (!pFind) {
    char* pInfo = mErrorAndStringBuffer->NewErrorInfo();
    if (pInfo)
      tsnprintf(pInfo, MAX_ERROR_INFO_CAPACITY, "[line %d ]:Block can't finish, delimiter: %s��", mLineNumber, delimiter);
    endToken();
    return;
  }
  int len = (int)strlen(delimiter);
  const char* p = pLeft;
  while (p != pFind){
    if (*p == '\n')
      ++mLineNumber;
    pushTokenChar(*p++);
    ++mIterator;
  }
  endToken();
  mIterator = mIterator + len;
  return removeFirstAndLastEmptyLine();
}

void SlkToken::removeFirstAndLastEmptyLine(void)
{
  int len = (int)strlen(mCurToken);
  int start = 0;
  while (start < len && isWhiteSpace(mCurToken[start]) && mCurToken[start] != '\n')
    ++start;
  if (mCurToken[start] == '\n')
    ++start;
  int end = len - 1;
  while (end > 0 && isWhiteSpace(mCurToken[end]) && mCurToken[end] != '\n') {
    mCurToken[end--] = 0;
  }
  mCurToken = &(mCurToken[start]);
}

void SlkToken::newComment(void)
{
  if (mErrorAndStringBuffer) {
    mCurComment = mErrorAndStringBuffer->GetUnusedStringPtrRef();

    mCommentCharIndex = 0;
    if (mCurComment) {
      mCurComment[mCommentCharIndex] = '\0';
    }
  }
}

void SlkToken::pushCommentChar(char c)
{
  if (NULL == mErrorAndStringBuffer || mErrorAndStringBuffer->GetUnusedStringLength() <= 1 || NULL == mCurComment)
    return;
  mCurComment[mCommentCharIndex] = c;
  ++mCommentCharIndex;
}

void SlkToken::endComment(void)
{
  if (NULL == mErrorAndStringBuffer || mErrorAndStringBuffer->GetUnusedStringLength() <= 1 || NULL == mCurComment || NULL == mErrorAndStringBuffer->GetUnusedStringPtrRef())
    return;
  mCurComment[mCommentCharIndex] = '\0';
  mErrorAndStringBuffer->GetUnusedStringPtrRef() += mCommentCharIndex + 1;

  mComments[mCommentNum++] = mCurComment;
}

void SlkToken::newToken(void)
{
  if (mErrorAndStringBuffer) {
    mLastToken = mCurToken;
    mLastLineNumber = mLineNumber;
    mCurToken = mErrorAndStringBuffer->GetUnusedStringPtrRef();

    mTokenCharIndex = 0;
    if (mCurToken) {
      mCurToken[mTokenCharIndex] = '\0';
    }
  }
}

void SlkToken::pushTokenChar(char c)
{
  if (NULL == mErrorAndStringBuffer || mErrorAndStringBuffer->GetUnusedStringLength() <= 1 || NULL == mCurToken)
    return;
  mCurToken[mTokenCharIndex] = c;
  ++mTokenCharIndex;
}

void SlkToken::endToken(void)
{
  if (NULL == mErrorAndStringBuffer || mErrorAndStringBuffer->GetUnusedStringLength() <= 1 || NULL == mCurToken || NULL == mErrorAndStringBuffer->GetUnusedStringPtrRef())
    return;
  mCurToken[mTokenCharIndex] = '\0';
  mErrorAndStringBuffer->GetUnusedStringPtrRef() += mTokenCharIndex + 1;
}

void SlkToken::endTokenWithEof(void)
{
  static const char* s_c_Eof = "<<eof>>";
  if (NULL == mErrorAndStringBuffer || mErrorAndStringBuffer->GetUnusedStringLength() <= (int)strlen(s_c_Eof) + 1 || NULL == mCurToken || NULL == mErrorAndStringBuffer->GetUnusedStringPtrRef())
    return;
  strcpy(mCurToken, s_c_Eof);
  mErrorAndStringBuffer->GetUnusedStringPtrRef() += strlen(s_c_Eof) + 1;
}

SlkToken::SlkToken(Dsl::IScriptSource& source, Dsl::ErrorAndStringBuffer& errorAndStringBuffer) :mSource(&source), mErrorAndStringBuffer(&errorAndStringBuffer)
{
  MyAssert(mSource);
  MyAssert(mErrorAndStringBuffer);

  mIterator = mSource->GetIterator();

  mWhiteSpaces = " \t\r\n";
  mDelimiters = "()[]{},;";
  mOperators = "~`!%^&*-+=|<>/?:";

  mLineNumber = 1;
  mLastLineNumber = 1;

  mCurToken = 0;
  mLastToken = 0;
  mTokenCharIndex = 0;

  mCurComment = 0;
  mCommentCharIndex = 0;
  mCommentNum = 0;
  mCommentOnNewLine = FALSE;

  setCanFinish(FALSE);
  setStringDelimiter("", "");
  setScriptDelimiter("", "");
}