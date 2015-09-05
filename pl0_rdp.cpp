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
void expect(Symbol s);
void accept(Symbol s);
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



  int ThisChar = getchar();
  LastChar = getchar();
  return ThisChar;
}

int main(void)
{

  printf("PARSE SUCCESS.\n");
  return 0;
}
