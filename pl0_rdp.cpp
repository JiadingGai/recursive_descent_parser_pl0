#include <iostream>
#include <string>
typedef enum {
  tok_eof = 5,
  ident,
  number,
  lparen,
  rparen,
  times,
  slash,
  plus,
  minus,
  eql,
  neq,
  lss,
  leq,
  gtr,
  geq,
  callsym,
  beginsym,
  semicolon,
  endsym,
  ifsym,
  whilesym,
  becomes,
  thensym,
  dosym,
  constsym,
  comma,
  varsym,
  procsym,
  period,
  oddsym,
  exclamationsym,
  questionsym
} Symbol;

Symbol sym;
void nextsym(void);
void error(const char *msg);
void block(void);
void statement(void);
void condition(void);
void term(void);
void factor(void);
void expression(void);
int expect(Symbol s);
int accept(Symbol s);
void program(void);

static std::string IdentifierStr;
static double NumVal;

static int gettok()
{
  static int LastChar = ' ';

  while (isspace(LastChar))
    LastChar = getchar();

  if (isalpha(LastChar)) {
    IdentifierStr = LastChar;
    while (isalnum(LastChar = getchar())) {
      IdentifierStr += LastChar;
    }

#if _DEBUG
    printf("[IdentifierStr] %s (followed by %c)\n", IdentifierStr.c_str(), LastChar);
#endif

    if (IdentifierStr == "call") return callsym;
    if (IdentifierStr == "begin") return beginsym;
    if (IdentifierStr == "end") return endsym;
    if (IdentifierStr == "if") return ifsym;
    if (IdentifierStr == "while") return whilesym;
    if (IdentifierStr == "then") return thensym;
    if (IdentifierStr == "do") return dosym;
    if (IdentifierStr == "const") return constsym;
    if (IdentifierStr == "var") return varsym;
    if (IdentifierStr == "procedure") return procsym;
    if (IdentifierStr == "odd") return oddsym;

    return ident;
  }

  //FIXME: not able to recognize numbers like .12345.
  //       because of the conflict with program period.
  if (isdigit(LastChar)/* || LastChar == '.'*/) {
    std::string NumStr;
    do {
      NumStr += LastChar;
      LastChar = getchar();
    } while (isdigit(LastChar) || LastChar == '.');

    NumVal = strtod(NumStr.c_str(), 0);
    return number;
  }

  if (LastChar == EOF)
    return tok_eof;

  if (LastChar == '*') {
    LastChar = getchar();
    return times;
  }

  if (LastChar == ',') {
    LastChar = getchar();
    return comma;
  }

  if (LastChar == '!') {
    LastChar = getchar();
    return exclamationsym;
  }

  if (LastChar == '?') {
    LastChar = getchar();
    return questionsym;
  }

  if (LastChar == ';') {
    LastChar = getchar();
    return semicolon;
  }

  if (LastChar == '+') {
    LastChar = getchar();
    return plus;
  }

  if (LastChar == '.') {
    return period;
  }

  if (LastChar == ':') {
    LastChar = getchar();
    if (LastChar == '=') {
      LastChar = getchar();
      return becomes;
    }
  }

  if (LastChar == '<') {
    LastChar = getchar();
    if (LastChar == '=') {
      LastChar = getchar();
      return leq;
    }
  }

  int ThisChar = getchar();
  LastChar = getchar();
  return ThisChar;
}

int main(void)
{
  program();
  printf("PARSE SUCCESS.\n");
  return 0;
}

static int CurTok;
void nextsym(void)
{
  CurTok = gettok();

#if _DEBUG
  sym = static_cast<Symbol>(CurTok);
  printf("[CurrentSymbol] %d\n", sym);
#endif
}

void program(void)
{
  nextsym();
  block();
  expect(period);
}

void block(void)
{

}

void statement(void)
{}

void condition(void)
{}

void expression(void)
{}

void term(void)
{}

void factor(void)
{}

int expect(Symbol s)
{
  if (accept(s)) {
    return 1;
  }

  printf("\n     [%d(%c), but expects %d(%c)]\n", sym, sym, s, s);
  error("[Expect] unexpected symbol.");
  return 0;
}

int accept(Symbol s)
{
  if (sym == s) {
    nextsym();
    return 1;
  }

  return 0;
}

void error(const char *msg)
{
  printf("ERROR: %s at %s:%d\n", msg, __FILE__, __LINE__);
  exit(1);
}
