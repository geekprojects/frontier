
// Generated from css3.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"




class  css3Lexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, Comment = 16, Space = 17, Cdo = 18, Cdc = 19, Includes = 20, 
    DashMatch = 21, Hash = 22, Import = 23, Page = 24, Media = 25, Namespace = 26, 
    Charset = 27, Important = 28, Percentage = 29, Uri = 30, UnicodeRange = 31, 
    MediaOnly = 32, Not = 33, And = 34, Dimension = 35, UnknownDimension = 36, 
    Plus = 37, Minus = 38, Greater = 39, Comma = 40, Tilde = 41, PseudoNot = 42, 
    Number = 43, String = 44, PrefixMatch = 45, SuffixMatch = 46, SubstringMatch = 47, 
    FontFace = 48, Supports = 49, Or = 50, Keyframes = 51, From = 52, To = 53, 
    Calc = 54, Viewport = 55, CounterStyle = 56, FontFeatureValues = 57, 
    DxImageTransform = 58, Variable = 59, Var = 60, Ident = 61, Function = 62
  };

  css3Lexer(antlr4::CharStream *input);
  ~css3Lexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getChannelNames() const override;
  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

