
// Generated from css3.g4 by ANTLR 4.7.2


#include "css3Listener.h"

#include "css3Parser.h"


using namespace antlrcpp;
using namespace antlr4;

css3Parser::css3Parser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

css3Parser::~css3Parser() {
  delete _interpreter;
}

std::string css3Parser::getGrammarFileName() const {
  return "css3.g4";
}

const std::vector<std::string>& css3Parser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& css3Parser::getVocabulary() const {
  return _vocabulary;
}


//----------------- StylesheetContext ------------------------------------------------------------------

css3Parser::StylesheetContext::StylesheetContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

css3Parser::WsContext* css3Parser::StylesheetContext::ws() {
  return getRuleContext<css3Parser::WsContext>(0);
}

std::vector<css3Parser::CharsetContext *> css3Parser::StylesheetContext::charset() {
  return getRuleContexts<css3Parser::CharsetContext>();
}

css3Parser::CharsetContext* css3Parser::StylesheetContext::charset(size_t i) {
  return getRuleContext<css3Parser::CharsetContext>(i);
}

std::vector<css3Parser::ImportsContext *> css3Parser::StylesheetContext::imports() {
  return getRuleContexts<css3Parser::ImportsContext>();
}

css3Parser::ImportsContext* css3Parser::StylesheetContext::imports(size_t i) {
  return getRuleContext<css3Parser::ImportsContext>(i);
}

std::vector<css3Parser::CssnamespaceContext *> css3Parser::StylesheetContext::cssnamespace() {
  return getRuleContexts<css3Parser::CssnamespaceContext>();
}

css3Parser::CssnamespaceContext* css3Parser::StylesheetContext::cssnamespace(size_t i) {
  return getRuleContext<css3Parser::CssnamespaceContext>(i);
}

std::vector<css3Parser::NestedStatementContext *> css3Parser::StylesheetContext::nestedStatement() {
  return getRuleContexts<css3Parser::NestedStatementContext>();
}

css3Parser::NestedStatementContext* css3Parser::StylesheetContext::nestedStatement(size_t i) {
  return getRuleContext<css3Parser::NestedStatementContext>(i);
}

std::vector<tree::TerminalNode *> css3Parser::StylesheetContext::Comment() {
  return getTokens(css3Parser::Comment);
}

tree::TerminalNode* css3Parser::StylesheetContext::Comment(size_t i) {
  return getToken(css3Parser::Comment, i);
}

std::vector<tree::TerminalNode *> css3Parser::StylesheetContext::Space() {
  return getTokens(css3Parser::Space);
}

tree::TerminalNode* css3Parser::StylesheetContext::Space(size_t i) {
  return getToken(css3Parser::Space, i);
}

std::vector<tree::TerminalNode *> css3Parser::StylesheetContext::Cdo() {
  return getTokens(css3Parser::Cdo);
}

tree::TerminalNode* css3Parser::StylesheetContext::Cdo(size_t i) {
  return getToken(css3Parser::Cdo, i);
}

std::vector<tree::TerminalNode *> css3Parser::StylesheetContext::Cdc() {
  return getTokens(css3Parser::Cdc);
}

tree::TerminalNode* css3Parser::StylesheetContext::Cdc(size_t i) {
  return getToken(css3Parser::Cdc, i);
}


size_t css3Parser::StylesheetContext::getRuleIndex() const {
  return css3Parser::RuleStylesheet;
}

void css3Parser::StylesheetContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStylesheet(this);
}

void css3Parser::StylesheetContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStylesheet(this);
}

css3Parser::StylesheetContext* css3Parser::stylesheet() {
  StylesheetContext *_localctx = _tracker.createInstance<StylesheetContext>(_ctx, getState());
  enterRule(_localctx, 0, css3Parser::RuleStylesheet);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(158);
    ws();
    setState(168);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == css3Parser::Charset) {
      setState(159);
      charset();
      setState(163);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << css3Parser::Comment)
        | (1ULL << css3Parser::Space)
        | (1ULL << css3Parser::Cdo)
        | (1ULL << css3Parser::Cdc))) != 0)) {
        setState(160);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << css3Parser::Comment)
          | (1ULL << css3Parser::Space)
          | (1ULL << css3Parser::Cdo)
          | (1ULL << css3Parser::Cdc))) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(165);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(170);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(180);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == css3Parser::Import) {
      setState(171);
      imports();
      setState(175);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << css3Parser::Comment)
        | (1ULL << css3Parser::Space)
        | (1ULL << css3Parser::Cdo)
        | (1ULL << css3Parser::Cdc))) != 0)) {
        setState(172);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << css3Parser::Comment)
          | (1ULL << css3Parser::Space)
          | (1ULL << css3Parser::Cdo)
          | (1ULL << css3Parser::Cdc))) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(177);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(182);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(192);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == css3Parser::Namespace) {
      setState(183);
      cssnamespace();
      setState(187);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << css3Parser::Comment)
        | (1ULL << css3Parser::Space)
        | (1ULL << css3Parser::Cdo)
        | (1ULL << css3Parser::Cdc))) != 0)) {
        setState(184);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << css3Parser::Comment)
          | (1ULL << css3Parser::Space)
          | (1ULL << css3Parser::Cdo)
          | (1ULL << css3Parser::Cdc))) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(189);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(194);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(204);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << css3Parser::T__1)
      | (1ULL << css3Parser::T__2)
      | (1ULL << css3Parser::T__4)
      | (1ULL << css3Parser::T__6)
      | (1ULL << css3Parser::T__7)
      | (1ULL << css3Parser::T__8)
      | (1ULL << css3Parser::T__9)
      | (1ULL << css3Parser::T__14)
      | (1ULL << css3Parser::Includes)
      | (1ULL << css3Parser::DashMatch)
      | (1ULL << css3Parser::Hash)
      | (1ULL << css3Parser::Page)
      | (1ULL << css3Parser::Media)
      | (1ULL << css3Parser::Percentage)
      | (1ULL << css3Parser::Uri)
      | (1ULL << css3Parser::UnicodeRange)
      | (1ULL << css3Parser::MediaOnly)
      | (1ULL << css3Parser::Not)
      | (1ULL << css3Parser::And)
      | (1ULL << css3Parser::Dimension)
      | (1ULL << css3Parser::UnknownDimension)
      | (1ULL << css3Parser::Plus)
      | (1ULL << css3Parser::Minus)
      | (1ULL << css3Parser::PseudoNot)
      | (1ULL << css3Parser::Number)
      | (1ULL << css3Parser::String)
      | (1ULL << css3Parser::FontFace)
      | (1ULL << css3Parser::Supports)
      | (1ULL << css3Parser::Or)
      | (1ULL << css3Parser::Keyframes)
      | (1ULL << css3Parser::From)
      | (1ULL << css3Parser::To)
      | (1ULL << css3Parser::Viewport)
      | (1ULL << css3Parser::CounterStyle)
      | (1ULL << css3Parser::FontFeatureValues)
      | (1ULL << css3Parser::Ident)
      | (1ULL << css3Parser::Function))) != 0)) {
      setState(195);
      nestedStatement();
      setState(199);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << css3Parser::Comment)
        | (1ULL << css3Parser::Space)
        | (1ULL << css3Parser::Cdo)
        | (1ULL << css3Parser::Cdc))) != 0)) {
        setState(196);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << css3Parser::Comment)
          | (1ULL << css3Parser::Space)
          | (1ULL << css3Parser::Cdo)
          | (1ULL << css3Parser::Cdc))) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(201);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(206);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CharsetContext ------------------------------------------------------------------

css3Parser::CharsetContext::CharsetContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t css3Parser::CharsetContext::getRuleIndex() const {
  return css3Parser::RuleCharset;
}

void css3Parser::CharsetContext::copyFrom(CharsetContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- BadCharsetContext ------------------------------------------------------------------

tree::TerminalNode* css3Parser::BadCharsetContext::Charset() {
  return getToken(css3Parser::Charset, 0);
}

std::vector<css3Parser::WsContext *> css3Parser::BadCharsetContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::BadCharsetContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}

tree::TerminalNode* css3Parser::BadCharsetContext::String() {
  return getToken(css3Parser::String, 0);
}

css3Parser::BadCharsetContext::BadCharsetContext(CharsetContext *ctx) { copyFrom(ctx); }

void css3Parser::BadCharsetContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBadCharset(this);
}
void css3Parser::BadCharsetContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBadCharset(this);
}
//----------------- GoodCharsetContext ------------------------------------------------------------------

tree::TerminalNode* css3Parser::GoodCharsetContext::Charset() {
  return getToken(css3Parser::Charset, 0);
}

std::vector<css3Parser::WsContext *> css3Parser::GoodCharsetContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::GoodCharsetContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}

tree::TerminalNode* css3Parser::GoodCharsetContext::String() {
  return getToken(css3Parser::String, 0);
}

css3Parser::GoodCharsetContext::GoodCharsetContext(CharsetContext *ctx) { copyFrom(ctx); }

void css3Parser::GoodCharsetContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGoodCharset(this);
}
void css3Parser::GoodCharsetContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGoodCharset(this);
}
css3Parser::CharsetContext* css3Parser::charset() {
  CharsetContext *_localctx = _tracker.createInstance<CharsetContext>(_ctx, getState());
  enterRule(_localctx, 2, css3Parser::RuleCharset);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(219);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<CharsetContext *>(_tracker.createInstance<css3Parser::GoodCharsetContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(207);
      match(css3Parser::Charset);
      setState(208);
      ws();
      setState(209);
      match(css3Parser::String);
      setState(210);
      ws();
      setState(211);
      match(css3Parser::T__0);
      setState(212);
      ws();
      break;
    }

    case 2: {
      _localctx = dynamic_cast<CharsetContext *>(_tracker.createInstance<css3Parser::BadCharsetContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(214);
      match(css3Parser::Charset);
      setState(215);
      ws();
      setState(216);
      match(css3Parser::String);
      setState(217);
      ws();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImportsContext ------------------------------------------------------------------

css3Parser::ImportsContext::ImportsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t css3Parser::ImportsContext::getRuleIndex() const {
  return css3Parser::RuleImports;
}

void css3Parser::ImportsContext::copyFrom(ImportsContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- BadImportContext ------------------------------------------------------------------

tree::TerminalNode* css3Parser::BadImportContext::Import() {
  return getToken(css3Parser::Import, 0);
}

std::vector<css3Parser::WsContext *> css3Parser::BadImportContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::BadImportContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}

css3Parser::MediaQueryListContext* css3Parser::BadImportContext::mediaQueryList() {
  return getRuleContext<css3Parser::MediaQueryListContext>(0);
}

tree::TerminalNode* css3Parser::BadImportContext::String() {
  return getToken(css3Parser::String, 0);
}

tree::TerminalNode* css3Parser::BadImportContext::Uri() {
  return getToken(css3Parser::Uri, 0);
}

css3Parser::BadImportContext::BadImportContext(ImportsContext *ctx) { copyFrom(ctx); }

void css3Parser::BadImportContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBadImport(this);
}
void css3Parser::BadImportContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBadImport(this);
}
//----------------- GoodImportContext ------------------------------------------------------------------

tree::TerminalNode* css3Parser::GoodImportContext::Import() {
  return getToken(css3Parser::Import, 0);
}

std::vector<css3Parser::WsContext *> css3Parser::GoodImportContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::GoodImportContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}

css3Parser::MediaQueryListContext* css3Parser::GoodImportContext::mediaQueryList() {
  return getRuleContext<css3Parser::MediaQueryListContext>(0);
}

tree::TerminalNode* css3Parser::GoodImportContext::String() {
  return getToken(css3Parser::String, 0);
}

tree::TerminalNode* css3Parser::GoodImportContext::Uri() {
  return getToken(css3Parser::Uri, 0);
}

css3Parser::GoodImportContext::GoodImportContext(ImportsContext *ctx) { copyFrom(ctx); }

void css3Parser::GoodImportContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGoodImport(this);
}
void css3Parser::GoodImportContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGoodImport(this);
}
css3Parser::ImportsContext* css3Parser::imports() {
  ImportsContext *_localctx = _tracker.createInstance<ImportsContext>(_ctx, getState());
  enterRule(_localctx, 4, css3Parser::RuleImports);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(247);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<ImportsContext *>(_tracker.createInstance<css3Parser::GoodImportContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(221);
      match(css3Parser::Import);
      setState(222);
      ws();
      setState(223);
      _la = _input->LA(1);
      if (!(_la == css3Parser::Uri

      || _la == css3Parser::String)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(224);
      ws();
      setState(225);
      mediaQueryList();
      setState(226);
      match(css3Parser::T__0);
      setState(227);
      ws();
      break;
    }

    case 2: {
      _localctx = dynamic_cast<ImportsContext *>(_tracker.createInstance<css3Parser::GoodImportContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(229);
      match(css3Parser::Import);
      setState(230);
      ws();
      setState(231);
      _la = _input->LA(1);
      if (!(_la == css3Parser::Uri

      || _la == css3Parser::String)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(232);
      ws();
      setState(233);
      match(css3Parser::T__0);
      setState(234);
      ws();
      break;
    }

    case 3: {
      _localctx = dynamic_cast<ImportsContext *>(_tracker.createInstance<css3Parser::BadImportContext>(_localctx));
      enterOuterAlt(_localctx, 3);
      setState(236);
      match(css3Parser::Import);
      setState(237);
      ws();
      setState(238);
      _la = _input->LA(1);
      if (!(_la == css3Parser::Uri

      || _la == css3Parser::String)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(239);
      ws();
      setState(240);
      mediaQueryList();
      break;
    }

    case 4: {
      _localctx = dynamic_cast<ImportsContext *>(_tracker.createInstance<css3Parser::BadImportContext>(_localctx));
      enterOuterAlt(_localctx, 4);
      setState(242);
      match(css3Parser::Import);
      setState(243);
      ws();
      setState(244);
      _la = _input->LA(1);
      if (!(_la == css3Parser::Uri

      || _la == css3Parser::String)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(245);
      ws();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CssnamespaceContext ------------------------------------------------------------------

css3Parser::CssnamespaceContext::CssnamespaceContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t css3Parser::CssnamespaceContext::getRuleIndex() const {
  return css3Parser::RuleCssnamespace;
}

void css3Parser::CssnamespaceContext::copyFrom(CssnamespaceContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- GoodNamespaceContext ------------------------------------------------------------------

tree::TerminalNode* css3Parser::GoodNamespaceContext::Namespace() {
  return getToken(css3Parser::Namespace, 0);
}

std::vector<css3Parser::WsContext *> css3Parser::GoodNamespaceContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::GoodNamespaceContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}

tree::TerminalNode* css3Parser::GoodNamespaceContext::String() {
  return getToken(css3Parser::String, 0);
}

tree::TerminalNode* css3Parser::GoodNamespaceContext::Uri() {
  return getToken(css3Parser::Uri, 0);
}

css3Parser::NamespacePrefixContext* css3Parser::GoodNamespaceContext::namespacePrefix() {
  return getRuleContext<css3Parser::NamespacePrefixContext>(0);
}

css3Parser::GoodNamespaceContext::GoodNamespaceContext(CssnamespaceContext *ctx) { copyFrom(ctx); }

void css3Parser::GoodNamespaceContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGoodNamespace(this);
}
void css3Parser::GoodNamespaceContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGoodNamespace(this);
}
//----------------- BadNamespaceContext ------------------------------------------------------------------

tree::TerminalNode* css3Parser::BadNamespaceContext::Namespace() {
  return getToken(css3Parser::Namespace, 0);
}

std::vector<css3Parser::WsContext *> css3Parser::BadNamespaceContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::BadNamespaceContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}

tree::TerminalNode* css3Parser::BadNamespaceContext::String() {
  return getToken(css3Parser::String, 0);
}

tree::TerminalNode* css3Parser::BadNamespaceContext::Uri() {
  return getToken(css3Parser::Uri, 0);
}

css3Parser::NamespacePrefixContext* css3Parser::BadNamespaceContext::namespacePrefix() {
  return getRuleContext<css3Parser::NamespacePrefixContext>(0);
}

css3Parser::BadNamespaceContext::BadNamespaceContext(CssnamespaceContext *ctx) { copyFrom(ctx); }

void css3Parser::BadNamespaceContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBadNamespace(this);
}
void css3Parser::BadNamespaceContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBadNamespace(this);
}
css3Parser::CssnamespaceContext* css3Parser::cssnamespace() {
  CssnamespaceContext *_localctx = _tracker.createInstance<CssnamespaceContext>(_ctx, getState());
  enterRule(_localctx, 6, css3Parser::RuleCssnamespace);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(271);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<CssnamespaceContext *>(_tracker.createInstance<css3Parser::GoodNamespaceContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(249);
      match(css3Parser::Namespace);
      setState(250);
      ws();
      setState(254);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << css3Parser::MediaOnly)
        | (1ULL << css3Parser::Not)
        | (1ULL << css3Parser::And)
        | (1ULL << css3Parser::Or)
        | (1ULL << css3Parser::From)
        | (1ULL << css3Parser::To)
        | (1ULL << css3Parser::Ident))) != 0)) {
        setState(251);
        namespacePrefix();
        setState(252);
        ws();
      }
      setState(256);
      _la = _input->LA(1);
      if (!(_la == css3Parser::Uri

      || _la == css3Parser::String)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(257);
      ws();
      setState(258);
      match(css3Parser::T__0);
      setState(259);
      ws();
      break;
    }

    case 2: {
      _localctx = dynamic_cast<CssnamespaceContext *>(_tracker.createInstance<css3Parser::BadNamespaceContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(261);
      match(css3Parser::Namespace);
      setState(262);
      ws();
      setState(266);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << css3Parser::MediaOnly)
        | (1ULL << css3Parser::Not)
        | (1ULL << css3Parser::And)
        | (1ULL << css3Parser::Or)
        | (1ULL << css3Parser::From)
        | (1ULL << css3Parser::To)
        | (1ULL << css3Parser::Ident))) != 0)) {
        setState(263);
        namespacePrefix();
        setState(264);
        ws();
      }
      setState(268);
      _la = _input->LA(1);
      if (!(_la == css3Parser::Uri

      || _la == css3Parser::String)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(269);
      ws();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NamespacePrefixContext ------------------------------------------------------------------

css3Parser::NamespacePrefixContext::NamespacePrefixContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

css3Parser::IdentContext* css3Parser::NamespacePrefixContext::ident() {
  return getRuleContext<css3Parser::IdentContext>(0);
}


size_t css3Parser::NamespacePrefixContext::getRuleIndex() const {
  return css3Parser::RuleNamespacePrefix;
}

void css3Parser::NamespacePrefixContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNamespacePrefix(this);
}

void css3Parser::NamespacePrefixContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNamespacePrefix(this);
}

css3Parser::NamespacePrefixContext* css3Parser::namespacePrefix() {
  NamespacePrefixContext *_localctx = _tracker.createInstance<NamespacePrefixContext>(_ctx, getState());
  enterRule(_localctx, 8, css3Parser::RuleNamespacePrefix);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(273);
    ident();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MediaContext ------------------------------------------------------------------

css3Parser::MediaContext::MediaContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* css3Parser::MediaContext::Media() {
  return getToken(css3Parser::Media, 0);
}

std::vector<css3Parser::WsContext *> css3Parser::MediaContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::MediaContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}

css3Parser::MediaQueryListContext* css3Parser::MediaContext::mediaQueryList() {
  return getRuleContext<css3Parser::MediaQueryListContext>(0);
}

css3Parser::GroupRuleBodyContext* css3Parser::MediaContext::groupRuleBody() {
  return getRuleContext<css3Parser::GroupRuleBodyContext>(0);
}


size_t css3Parser::MediaContext::getRuleIndex() const {
  return css3Parser::RuleMedia;
}

void css3Parser::MediaContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMedia(this);
}

void css3Parser::MediaContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMedia(this);
}

css3Parser::MediaContext* css3Parser::media() {
  MediaContext *_localctx = _tracker.createInstance<MediaContext>(_ctx, getState());
  enterRule(_localctx, 10, css3Parser::RuleMedia);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(275);
    match(css3Parser::Media);
    setState(276);
    ws();
    setState(277);
    mediaQueryList();
    setState(278);
    groupRuleBody();
    setState(279);
    ws();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MediaQueryListContext ------------------------------------------------------------------

css3Parser::MediaQueryListContext::MediaQueryListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<css3Parser::WsContext *> css3Parser::MediaQueryListContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::MediaQueryListContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}

std::vector<css3Parser::MediaQueryContext *> css3Parser::MediaQueryListContext::mediaQuery() {
  return getRuleContexts<css3Parser::MediaQueryContext>();
}

css3Parser::MediaQueryContext* css3Parser::MediaQueryListContext::mediaQuery(size_t i) {
  return getRuleContext<css3Parser::MediaQueryContext>(i);
}

std::vector<tree::TerminalNode *> css3Parser::MediaQueryListContext::Comma() {
  return getTokens(css3Parser::Comma);
}

tree::TerminalNode* css3Parser::MediaQueryListContext::Comma(size_t i) {
  return getToken(css3Parser::Comma, i);
}


size_t css3Parser::MediaQueryListContext::getRuleIndex() const {
  return css3Parser::RuleMediaQueryList;
}

void css3Parser::MediaQueryListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMediaQueryList(this);
}

void css3Parser::MediaQueryListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMediaQueryList(this);
}

css3Parser::MediaQueryListContext* css3Parser::mediaQueryList() {
  MediaQueryListContext *_localctx = _tracker.createInstance<MediaQueryListContext>(_ctx, getState());
  enterRule(_localctx, 12, css3Parser::RuleMediaQueryList);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(291);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
    case 1: {
      setState(281);
      mediaQuery();
      setState(288);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == css3Parser::Comma) {
        setState(282);
        match(css3Parser::Comma);
        setState(283);
        ws();
        setState(284);
        mediaQuery();
        setState(290);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      break;
    }

    }
    setState(293);
    ws();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MediaQueryContext ------------------------------------------------------------------

css3Parser::MediaQueryContext::MediaQueryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<css3Parser::WsContext *> css3Parser::MediaQueryContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::MediaQueryContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}

css3Parser::MediaTypeContext* css3Parser::MediaQueryContext::mediaType() {
  return getRuleContext<css3Parser::MediaTypeContext>(0);
}

std::vector<tree::TerminalNode *> css3Parser::MediaQueryContext::And() {
  return getTokens(css3Parser::And);
}

tree::TerminalNode* css3Parser::MediaQueryContext::And(size_t i) {
  return getToken(css3Parser::And, i);
}

std::vector<css3Parser::MediaExpressionContext *> css3Parser::MediaQueryContext::mediaExpression() {
  return getRuleContexts<css3Parser::MediaExpressionContext>();
}

css3Parser::MediaExpressionContext* css3Parser::MediaQueryContext::mediaExpression(size_t i) {
  return getRuleContext<css3Parser::MediaExpressionContext>(i);
}

tree::TerminalNode* css3Parser::MediaQueryContext::MediaOnly() {
  return getToken(css3Parser::MediaOnly, 0);
}

tree::TerminalNode* css3Parser::MediaQueryContext::Not() {
  return getToken(css3Parser::Not, 0);
}


size_t css3Parser::MediaQueryContext::getRuleIndex() const {
  return css3Parser::RuleMediaQuery;
}

void css3Parser::MediaQueryContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMediaQuery(this);
}

void css3Parser::MediaQueryContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMediaQuery(this);
}

css3Parser::MediaQueryContext* css3Parser::mediaQuery() {
  MediaQueryContext *_localctx = _tracker.createInstance<MediaQueryContext>(_ctx, getState());
  enterRule(_localctx, 14, css3Parser::RuleMediaQuery);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    setState(320);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case css3Parser::Comment:
      case css3Parser::Space:
      case css3Parser::MediaOnly:
      case css3Parser::Not:
      case css3Parser::And:
      case css3Parser::Or:
      case css3Parser::From:
      case css3Parser::To:
      case css3Parser::Ident: {
        enterOuterAlt(_localctx, 1);
        setState(296);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
        case 1: {
          setState(295);
          _la = _input->LA(1);
          if (!(_la == css3Parser::MediaOnly

          || _la == css3Parser::Not)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          break;
        }

        }
        setState(298);
        ws();
        setState(299);
        mediaType();
        setState(300);
        ws();
        setState(307);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
          if (alt == 1) {
            setState(301);
            match(css3Parser::And);
            setState(302);
            ws();
            setState(303);
            mediaExpression(); 
          }
          setState(309);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
        }
        break;
      }

      case css3Parser::T__1: {
        enterOuterAlt(_localctx, 2);
        setState(310);
        mediaExpression();
        setState(317);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
          if (alt == 1) {
            setState(311);
            match(css3Parser::And);
            setState(312);
            ws();
            setState(313);
            mediaExpression(); 
          }
          setState(319);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx);
        }
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MediaTypeContext ------------------------------------------------------------------

css3Parser::MediaTypeContext::MediaTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

css3Parser::IdentContext* css3Parser::MediaTypeContext::ident() {
  return getRuleContext<css3Parser::IdentContext>(0);
}


size_t css3Parser::MediaTypeContext::getRuleIndex() const {
  return css3Parser::RuleMediaType;
}

void css3Parser::MediaTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMediaType(this);
}

void css3Parser::MediaTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMediaType(this);
}

css3Parser::MediaTypeContext* css3Parser::mediaType() {
  MediaTypeContext *_localctx = _tracker.createInstance<MediaTypeContext>(_ctx, getState());
  enterRule(_localctx, 16, css3Parser::RuleMediaType);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(322);
    ident();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MediaExpressionContext ------------------------------------------------------------------

css3Parser::MediaExpressionContext::MediaExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<css3Parser::WsContext *> css3Parser::MediaExpressionContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::MediaExpressionContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}

css3Parser::MediaFeatureContext* css3Parser::MediaExpressionContext::mediaFeature() {
  return getRuleContext<css3Parser::MediaFeatureContext>(0);
}

css3Parser::ExprContext* css3Parser::MediaExpressionContext::expr() {
  return getRuleContext<css3Parser::ExprContext>(0);
}


size_t css3Parser::MediaExpressionContext::getRuleIndex() const {
  return css3Parser::RuleMediaExpression;
}

void css3Parser::MediaExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMediaExpression(this);
}

void css3Parser::MediaExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMediaExpression(this);
}

css3Parser::MediaExpressionContext* css3Parser::mediaExpression() {
  MediaExpressionContext *_localctx = _tracker.createInstance<MediaExpressionContext>(_ctx, getState());
  enterRule(_localctx, 18, css3Parser::RuleMediaExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(324);
    match(css3Parser::T__1);
    setState(325);
    ws();
    setState(326);
    mediaFeature();
    setState(331);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == css3Parser::T__2) {
      setState(327);
      match(css3Parser::T__2);
      setState(328);
      ws();
      setState(329);
      expr();
    }
    setState(333);
    match(css3Parser::T__3);
    setState(334);
    ws();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MediaFeatureContext ------------------------------------------------------------------

css3Parser::MediaFeatureContext::MediaFeatureContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

css3Parser::IdentContext* css3Parser::MediaFeatureContext::ident() {
  return getRuleContext<css3Parser::IdentContext>(0);
}

css3Parser::WsContext* css3Parser::MediaFeatureContext::ws() {
  return getRuleContext<css3Parser::WsContext>(0);
}


size_t css3Parser::MediaFeatureContext::getRuleIndex() const {
  return css3Parser::RuleMediaFeature;
}

void css3Parser::MediaFeatureContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMediaFeature(this);
}

void css3Parser::MediaFeatureContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMediaFeature(this);
}

css3Parser::MediaFeatureContext* css3Parser::mediaFeature() {
  MediaFeatureContext *_localctx = _tracker.createInstance<MediaFeatureContext>(_ctx, getState());
  enterRule(_localctx, 20, css3Parser::RuleMediaFeature);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(336);
    ident();
    setState(337);
    ws();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PageContext ------------------------------------------------------------------

css3Parser::PageContext::PageContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* css3Parser::PageContext::Page() {
  return getToken(css3Parser::Page, 0);
}

std::vector<css3Parser::WsContext *> css3Parser::PageContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::PageContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}

css3Parser::PseudoPageContext* css3Parser::PageContext::pseudoPage() {
  return getRuleContext<css3Parser::PseudoPageContext>(0);
}

std::vector<css3Parser::DeclarationContext *> css3Parser::PageContext::declaration() {
  return getRuleContexts<css3Parser::DeclarationContext>();
}

css3Parser::DeclarationContext* css3Parser::PageContext::declaration(size_t i) {
  return getRuleContext<css3Parser::DeclarationContext>(i);
}


size_t css3Parser::PageContext::getRuleIndex() const {
  return css3Parser::RulePage;
}

void css3Parser::PageContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPage(this);
}

void css3Parser::PageContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPage(this);
}

css3Parser::PageContext* css3Parser::page() {
  PageContext *_localctx = _tracker.createInstance<PageContext>(_ctx, getState());
  enterRule(_localctx, 22, css3Parser::RulePage);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(339);
    match(css3Parser::Page);
    setState(340);
    ws();
    setState(342);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == css3Parser::T__2) {
      setState(341);
      pseudoPage();
    }
    setState(344);
    match(css3Parser::T__4);
    setState(345);
    ws();
    setState(347);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << css3Parser::T__6)
      | (1ULL << css3Parser::T__13)
      | (1ULL << css3Parser::MediaOnly)
      | (1ULL << css3Parser::Not)
      | (1ULL << css3Parser::And)
      | (1ULL << css3Parser::Or)
      | (1ULL << css3Parser::From)
      | (1ULL << css3Parser::To)
      | (1ULL << css3Parser::Variable)
      | (1ULL << css3Parser::Ident))) != 0)) {
      setState(346);
      declaration();
    }
    setState(356);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == css3Parser::T__0) {
      setState(349);
      match(css3Parser::T__0);
      setState(350);
      ws();
      setState(352);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << css3Parser::T__6)
        | (1ULL << css3Parser::T__13)
        | (1ULL << css3Parser::MediaOnly)
        | (1ULL << css3Parser::Not)
        | (1ULL << css3Parser::And)
        | (1ULL << css3Parser::Or)
        | (1ULL << css3Parser::From)
        | (1ULL << css3Parser::To)
        | (1ULL << css3Parser::Variable)
        | (1ULL << css3Parser::Ident))) != 0)) {
        setState(351);
        declaration();
      }
      setState(358);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(359);
    match(css3Parser::T__5);
    setState(360);
    ws();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PseudoPageContext ------------------------------------------------------------------

css3Parser::PseudoPageContext::PseudoPageContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

css3Parser::IdentContext* css3Parser::PseudoPageContext::ident() {
  return getRuleContext<css3Parser::IdentContext>(0);
}

css3Parser::WsContext* css3Parser::PseudoPageContext::ws() {
  return getRuleContext<css3Parser::WsContext>(0);
}


size_t css3Parser::PseudoPageContext::getRuleIndex() const {
  return css3Parser::RulePseudoPage;
}

void css3Parser::PseudoPageContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPseudoPage(this);
}

void css3Parser::PseudoPageContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPseudoPage(this);
}

css3Parser::PseudoPageContext* css3Parser::pseudoPage() {
  PseudoPageContext *_localctx = _tracker.createInstance<PseudoPageContext>(_ctx, getState());
  enterRule(_localctx, 24, css3Parser::RulePseudoPage);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(362);
    match(css3Parser::T__2);
    setState(363);
    ident();
    setState(364);
    ws();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SelectorGroupContext ------------------------------------------------------------------

css3Parser::SelectorGroupContext::SelectorGroupContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<css3Parser::SelectorContext *> css3Parser::SelectorGroupContext::selector() {
  return getRuleContexts<css3Parser::SelectorContext>();
}

css3Parser::SelectorContext* css3Parser::SelectorGroupContext::selector(size_t i) {
  return getRuleContext<css3Parser::SelectorContext>(i);
}

std::vector<tree::TerminalNode *> css3Parser::SelectorGroupContext::Comma() {
  return getTokens(css3Parser::Comma);
}

tree::TerminalNode* css3Parser::SelectorGroupContext::Comma(size_t i) {
  return getToken(css3Parser::Comma, i);
}

std::vector<css3Parser::WsContext *> css3Parser::SelectorGroupContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::SelectorGroupContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}


size_t css3Parser::SelectorGroupContext::getRuleIndex() const {
  return css3Parser::RuleSelectorGroup;
}

void css3Parser::SelectorGroupContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSelectorGroup(this);
}

void css3Parser::SelectorGroupContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSelectorGroup(this);
}

css3Parser::SelectorGroupContext* css3Parser::selectorGroup() {
  SelectorGroupContext *_localctx = _tracker.createInstance<SelectorGroupContext>(_ctx, getState());
  enterRule(_localctx, 26, css3Parser::RuleSelectorGroup);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(366);
    selector();
    setState(373);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == css3Parser::Comma) {
      setState(367);
      match(css3Parser::Comma);
      setState(368);
      ws();
      setState(369);
      selector();
      setState(375);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SelectorContext ------------------------------------------------------------------

css3Parser::SelectorContext::SelectorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<css3Parser::SimpleSelectorSequenceContext *> css3Parser::SelectorContext::simpleSelectorSequence() {
  return getRuleContexts<css3Parser::SimpleSelectorSequenceContext>();
}

css3Parser::SimpleSelectorSequenceContext* css3Parser::SelectorContext::simpleSelectorSequence(size_t i) {
  return getRuleContext<css3Parser::SimpleSelectorSequenceContext>(i);
}

std::vector<css3Parser::WsContext *> css3Parser::SelectorContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::SelectorContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}

std::vector<css3Parser::CombinatorContext *> css3Parser::SelectorContext::combinator() {
  return getRuleContexts<css3Parser::CombinatorContext>();
}

css3Parser::CombinatorContext* css3Parser::SelectorContext::combinator(size_t i) {
  return getRuleContext<css3Parser::CombinatorContext>(i);
}


size_t css3Parser::SelectorContext::getRuleIndex() const {
  return css3Parser::RuleSelector;
}

void css3Parser::SelectorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSelector(this);
}

void css3Parser::SelectorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSelector(this);
}

css3Parser::SelectorContext* css3Parser::selector() {
  SelectorContext *_localctx = _tracker.createInstance<SelectorContext>(_ctx, getState());
  enterRule(_localctx, 28, css3Parser::RuleSelector);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(376);
    simpleSelectorSequence();
    setState(377);
    ws();
    setState(384);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << css3Parser::Space)
      | (1ULL << css3Parser::Plus)
      | (1ULL << css3Parser::Greater)
      | (1ULL << css3Parser::Tilde))) != 0)) {
      setState(378);
      combinator();
      setState(379);
      simpleSelectorSequence();
      setState(380);
      ws();
      setState(386);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CombinatorContext ------------------------------------------------------------------

css3Parser::CombinatorContext::CombinatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* css3Parser::CombinatorContext::Plus() {
  return getToken(css3Parser::Plus, 0);
}

css3Parser::WsContext* css3Parser::CombinatorContext::ws() {
  return getRuleContext<css3Parser::WsContext>(0);
}

tree::TerminalNode* css3Parser::CombinatorContext::Greater() {
  return getToken(css3Parser::Greater, 0);
}

tree::TerminalNode* css3Parser::CombinatorContext::Tilde() {
  return getToken(css3Parser::Tilde, 0);
}

tree::TerminalNode* css3Parser::CombinatorContext::Space() {
  return getToken(css3Parser::Space, 0);
}


size_t css3Parser::CombinatorContext::getRuleIndex() const {
  return css3Parser::RuleCombinator;
}

void css3Parser::CombinatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCombinator(this);
}

void css3Parser::CombinatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCombinator(this);
}

css3Parser::CombinatorContext* css3Parser::combinator() {
  CombinatorContext *_localctx = _tracker.createInstance<CombinatorContext>(_ctx, getState());
  enterRule(_localctx, 30, css3Parser::RuleCombinator);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(395);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case css3Parser::Plus: {
        enterOuterAlt(_localctx, 1);
        setState(387);
        match(css3Parser::Plus);
        setState(388);
        ws();
        break;
      }

      case css3Parser::Greater: {
        enterOuterAlt(_localctx, 2);
        setState(389);
        match(css3Parser::Greater);
        setState(390);
        ws();
        break;
      }

      case css3Parser::Tilde: {
        enterOuterAlt(_localctx, 3);
        setState(391);
        match(css3Parser::Tilde);
        setState(392);
        ws();
        break;
      }

      case css3Parser::Space: {
        enterOuterAlt(_localctx, 4);
        setState(393);
        match(css3Parser::Space);
        setState(394);
        ws();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SimpleSelectorSequenceContext ------------------------------------------------------------------

css3Parser::SimpleSelectorSequenceContext::SimpleSelectorSequenceContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

css3Parser::TypeSelectorContext* css3Parser::SimpleSelectorSequenceContext::typeSelector() {
  return getRuleContext<css3Parser::TypeSelectorContext>(0);
}

css3Parser::UniversalContext* css3Parser::SimpleSelectorSequenceContext::universal() {
  return getRuleContext<css3Parser::UniversalContext>(0);
}

std::vector<tree::TerminalNode *> css3Parser::SimpleSelectorSequenceContext::Hash() {
  return getTokens(css3Parser::Hash);
}

tree::TerminalNode* css3Parser::SimpleSelectorSequenceContext::Hash(size_t i) {
  return getToken(css3Parser::Hash, i);
}

std::vector<css3Parser::ClassNameContext *> css3Parser::SimpleSelectorSequenceContext::className() {
  return getRuleContexts<css3Parser::ClassNameContext>();
}

css3Parser::ClassNameContext* css3Parser::SimpleSelectorSequenceContext::className(size_t i) {
  return getRuleContext<css3Parser::ClassNameContext>(i);
}

std::vector<css3Parser::AttribContext *> css3Parser::SimpleSelectorSequenceContext::attrib() {
  return getRuleContexts<css3Parser::AttribContext>();
}

css3Parser::AttribContext* css3Parser::SimpleSelectorSequenceContext::attrib(size_t i) {
  return getRuleContext<css3Parser::AttribContext>(i);
}

std::vector<css3Parser::PseudoContext *> css3Parser::SimpleSelectorSequenceContext::pseudo() {
  return getRuleContexts<css3Parser::PseudoContext>();
}

css3Parser::PseudoContext* css3Parser::SimpleSelectorSequenceContext::pseudo(size_t i) {
  return getRuleContext<css3Parser::PseudoContext>(i);
}

std::vector<css3Parser::NegationContext *> css3Parser::SimpleSelectorSequenceContext::negation() {
  return getRuleContexts<css3Parser::NegationContext>();
}

css3Parser::NegationContext* css3Parser::SimpleSelectorSequenceContext::negation(size_t i) {
  return getRuleContext<css3Parser::NegationContext>(i);
}


size_t css3Parser::SimpleSelectorSequenceContext::getRuleIndex() const {
  return css3Parser::RuleSimpleSelectorSequence;
}

void css3Parser::SimpleSelectorSequenceContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSimpleSelectorSequence(this);
}

void css3Parser::SimpleSelectorSequenceContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSimpleSelectorSequence(this);
}

css3Parser::SimpleSelectorSequenceContext* css3Parser::simpleSelectorSequence() {
  SimpleSelectorSequenceContext *_localctx = _tracker.createInstance<SimpleSelectorSequenceContext>(_ctx, getState());
  enterRule(_localctx, 32, css3Parser::RuleSimpleSelectorSequence);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(420);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case css3Parser::T__6:
      case css3Parser::T__7:
      case css3Parser::MediaOnly:
      case css3Parser::Not:
      case css3Parser::And:
      case css3Parser::Or:
      case css3Parser::From:
      case css3Parser::To:
      case css3Parser::Ident: {
        enterOuterAlt(_localctx, 1);
        setState(399);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx)) {
        case 1: {
          setState(397);
          typeSelector();
          break;
        }

        case 2: {
          setState(398);
          universal();
          break;
        }

        }
        setState(408);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << css3Parser::T__2)
          | (1ULL << css3Parser::T__8)
          | (1ULL << css3Parser::T__9)
          | (1ULL << css3Parser::Hash)
          | (1ULL << css3Parser::PseudoNot))) != 0)) {
          setState(406);
          _errHandler->sync(this);
          switch (_input->LA(1)) {
            case css3Parser::Hash: {
              setState(401);
              match(css3Parser::Hash);
              break;
            }

            case css3Parser::T__8: {
              setState(402);
              className();
              break;
            }

            case css3Parser::T__9: {
              setState(403);
              attrib();
              break;
            }

            case css3Parser::T__2: {
              setState(404);
              pseudo();
              break;
            }

            case css3Parser::PseudoNot: {
              setState(405);
              negation();
              break;
            }

          default:
            throw NoViableAltException(this);
          }
          setState(410);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        break;
      }

      case css3Parser::T__2:
      case css3Parser::T__8:
      case css3Parser::T__9:
      case css3Parser::Hash:
      case css3Parser::PseudoNot: {
        enterOuterAlt(_localctx, 2);
        setState(416); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(416);
          _errHandler->sync(this);
          switch (_input->LA(1)) {
            case css3Parser::Hash: {
              setState(411);
              match(css3Parser::Hash);
              break;
            }

            case css3Parser::T__8: {
              setState(412);
              className();
              break;
            }

            case css3Parser::T__9: {
              setState(413);
              attrib();
              break;
            }

            case css3Parser::T__2: {
              setState(414);
              pseudo();
              break;
            }

            case css3Parser::PseudoNot: {
              setState(415);
              negation();
              break;
            }

          default:
            throw NoViableAltException(this);
          }
          setState(418); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << css3Parser::T__2)
          | (1ULL << css3Parser::T__8)
          | (1ULL << css3Parser::T__9)
          | (1ULL << css3Parser::Hash)
          | (1ULL << css3Parser::PseudoNot))) != 0));
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeSelectorContext ------------------------------------------------------------------

css3Parser::TypeSelectorContext::TypeSelectorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

css3Parser::ElementNameContext* css3Parser::TypeSelectorContext::elementName() {
  return getRuleContext<css3Parser::ElementNameContext>(0);
}

css3Parser::TypeNamespacePrefixContext* css3Parser::TypeSelectorContext::typeNamespacePrefix() {
  return getRuleContext<css3Parser::TypeNamespacePrefixContext>(0);
}


size_t css3Parser::TypeSelectorContext::getRuleIndex() const {
  return css3Parser::RuleTypeSelector;
}

void css3Parser::TypeSelectorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeSelector(this);
}

void css3Parser::TypeSelectorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeSelector(this);
}

css3Parser::TypeSelectorContext* css3Parser::typeSelector() {
  TypeSelectorContext *_localctx = _tracker.createInstance<TypeSelectorContext>(_ctx, getState());
  enterRule(_localctx, 34, css3Parser::RuleTypeSelector);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(423);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx)) {
    case 1: {
      setState(422);
      typeNamespacePrefix();
      break;
    }

    }
    setState(425);
    elementName();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeNamespacePrefixContext ------------------------------------------------------------------

css3Parser::TypeNamespacePrefixContext::TypeNamespacePrefixContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

css3Parser::IdentContext* css3Parser::TypeNamespacePrefixContext::ident() {
  return getRuleContext<css3Parser::IdentContext>(0);
}


size_t css3Parser::TypeNamespacePrefixContext::getRuleIndex() const {
  return css3Parser::RuleTypeNamespacePrefix;
}

void css3Parser::TypeNamespacePrefixContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeNamespacePrefix(this);
}

void css3Parser::TypeNamespacePrefixContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeNamespacePrefix(this);
}

css3Parser::TypeNamespacePrefixContext* css3Parser::typeNamespacePrefix() {
  TypeNamespacePrefixContext *_localctx = _tracker.createInstance<TypeNamespacePrefixContext>(_ctx, getState());
  enterRule(_localctx, 36, css3Parser::RuleTypeNamespacePrefix);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(429);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case css3Parser::MediaOnly:
      case css3Parser::Not:
      case css3Parser::And:
      case css3Parser::Or:
      case css3Parser::From:
      case css3Parser::To:
      case css3Parser::Ident: {
        setState(427);
        ident();
        break;
      }

      case css3Parser::T__6: {
        setState(428);
        match(css3Parser::T__6);
        break;
      }

      case css3Parser::T__7: {
        break;
      }

    default:
      break;
    }
    setState(431);
    match(css3Parser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElementNameContext ------------------------------------------------------------------

css3Parser::ElementNameContext::ElementNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

css3Parser::IdentContext* css3Parser::ElementNameContext::ident() {
  return getRuleContext<css3Parser::IdentContext>(0);
}


size_t css3Parser::ElementNameContext::getRuleIndex() const {
  return css3Parser::RuleElementName;
}

void css3Parser::ElementNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElementName(this);
}

void css3Parser::ElementNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElementName(this);
}

css3Parser::ElementNameContext* css3Parser::elementName() {
  ElementNameContext *_localctx = _tracker.createInstance<ElementNameContext>(_ctx, getState());
  enterRule(_localctx, 38, css3Parser::RuleElementName);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(433);
    ident();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UniversalContext ------------------------------------------------------------------

css3Parser::UniversalContext::UniversalContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

css3Parser::TypeNamespacePrefixContext* css3Parser::UniversalContext::typeNamespacePrefix() {
  return getRuleContext<css3Parser::TypeNamespacePrefixContext>(0);
}


size_t css3Parser::UniversalContext::getRuleIndex() const {
  return css3Parser::RuleUniversal;
}

void css3Parser::UniversalContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUniversal(this);
}

void css3Parser::UniversalContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUniversal(this);
}

css3Parser::UniversalContext* css3Parser::universal() {
  UniversalContext *_localctx = _tracker.createInstance<UniversalContext>(_ctx, getState());
  enterRule(_localctx, 40, css3Parser::RuleUniversal);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(436);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx)) {
    case 1: {
      setState(435);
      typeNamespacePrefix();
      break;
    }

    }
    setState(438);
    match(css3Parser::T__6);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClassNameContext ------------------------------------------------------------------

css3Parser::ClassNameContext::ClassNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

css3Parser::IdentContext* css3Parser::ClassNameContext::ident() {
  return getRuleContext<css3Parser::IdentContext>(0);
}


size_t css3Parser::ClassNameContext::getRuleIndex() const {
  return css3Parser::RuleClassName;
}

void css3Parser::ClassNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterClassName(this);
}

void css3Parser::ClassNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitClassName(this);
}

css3Parser::ClassNameContext* css3Parser::className() {
  ClassNameContext *_localctx = _tracker.createInstance<ClassNameContext>(_ctx, getState());
  enterRule(_localctx, 42, css3Parser::RuleClassName);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(440);
    match(css3Parser::T__8);
    setState(441);
    ident();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AttribContext ------------------------------------------------------------------

css3Parser::AttribContext::AttribContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<css3Parser::WsContext *> css3Parser::AttribContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::AttribContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}

std::vector<css3Parser::IdentContext *> css3Parser::AttribContext::ident() {
  return getRuleContexts<css3Parser::IdentContext>();
}

css3Parser::IdentContext* css3Parser::AttribContext::ident(size_t i) {
  return getRuleContext<css3Parser::IdentContext>(i);
}

css3Parser::TypeNamespacePrefixContext* css3Parser::AttribContext::typeNamespacePrefix() {
  return getRuleContext<css3Parser::TypeNamespacePrefixContext>(0);
}

tree::TerminalNode* css3Parser::AttribContext::PrefixMatch() {
  return getToken(css3Parser::PrefixMatch, 0);
}

tree::TerminalNode* css3Parser::AttribContext::SuffixMatch() {
  return getToken(css3Parser::SuffixMatch, 0);
}

tree::TerminalNode* css3Parser::AttribContext::SubstringMatch() {
  return getToken(css3Parser::SubstringMatch, 0);
}

tree::TerminalNode* css3Parser::AttribContext::Includes() {
  return getToken(css3Parser::Includes, 0);
}

tree::TerminalNode* css3Parser::AttribContext::DashMatch() {
  return getToken(css3Parser::DashMatch, 0);
}

tree::TerminalNode* css3Parser::AttribContext::String() {
  return getToken(css3Parser::String, 0);
}


size_t css3Parser::AttribContext::getRuleIndex() const {
  return css3Parser::RuleAttrib;
}

void css3Parser::AttribContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAttrib(this);
}

void css3Parser::AttribContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAttrib(this);
}

css3Parser::AttribContext* css3Parser::attrib() {
  AttribContext *_localctx = _tracker.createInstance<AttribContext>(_ctx, getState());
  enterRule(_localctx, 44, css3Parser::RuleAttrib);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(443);
    match(css3Parser::T__9);
    setState(444);
    ws();
    setState(446);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx)) {
    case 1: {
      setState(445);
      typeNamespacePrefix();
      break;
    }

    }
    setState(448);
    ident();
    setState(449);
    ws();
    setState(458);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << css3Parser::T__10)
      | (1ULL << css3Parser::Includes)
      | (1ULL << css3Parser::DashMatch)
      | (1ULL << css3Parser::PrefixMatch)
      | (1ULL << css3Parser::SuffixMatch)
      | (1ULL << css3Parser::SubstringMatch))) != 0)) {
      setState(450);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << css3Parser::T__10)
        | (1ULL << css3Parser::Includes)
        | (1ULL << css3Parser::DashMatch)
        | (1ULL << css3Parser::PrefixMatch)
        | (1ULL << css3Parser::SuffixMatch)
        | (1ULL << css3Parser::SubstringMatch))) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(451);
      ws();
      setState(454);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case css3Parser::MediaOnly:
        case css3Parser::Not:
        case css3Parser::And:
        case css3Parser::Or:
        case css3Parser::From:
        case css3Parser::To:
        case css3Parser::Ident: {
          setState(452);
          ident();
          break;
        }

        case css3Parser::String: {
          setState(453);
          match(css3Parser::String);
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(456);
      ws();
    }
    setState(460);
    match(css3Parser::T__11);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PseudoContext ------------------------------------------------------------------

css3Parser::PseudoContext::PseudoContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

css3Parser::IdentContext* css3Parser::PseudoContext::ident() {
  return getRuleContext<css3Parser::IdentContext>(0);
}

css3Parser::FunctionalPseudoContext* css3Parser::PseudoContext::functionalPseudo() {
  return getRuleContext<css3Parser::FunctionalPseudoContext>(0);
}


size_t css3Parser::PseudoContext::getRuleIndex() const {
  return css3Parser::RulePseudo;
}

void css3Parser::PseudoContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPseudo(this);
}

void css3Parser::PseudoContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPseudo(this);
}

css3Parser::PseudoContext* css3Parser::pseudo() {
  PseudoContext *_localctx = _tracker.createInstance<PseudoContext>(_ctx, getState());
  enterRule(_localctx, 46, css3Parser::RulePseudo);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(462);
    match(css3Parser::T__2);
    setState(464);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == css3Parser::T__2) {
      setState(463);
      match(css3Parser::T__2);
    }
    setState(468);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case css3Parser::MediaOnly:
      case css3Parser::Not:
      case css3Parser::And:
      case css3Parser::Or:
      case css3Parser::From:
      case css3Parser::To:
      case css3Parser::Ident: {
        setState(466);
        ident();
        break;
      }

      case css3Parser::Function: {
        setState(467);
        functionalPseudo();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionalPseudoContext ------------------------------------------------------------------

css3Parser::FunctionalPseudoContext::FunctionalPseudoContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* css3Parser::FunctionalPseudoContext::Function() {
  return getToken(css3Parser::Function, 0);
}

css3Parser::WsContext* css3Parser::FunctionalPseudoContext::ws() {
  return getRuleContext<css3Parser::WsContext>(0);
}

css3Parser::ExpressionContext* css3Parser::FunctionalPseudoContext::expression() {
  return getRuleContext<css3Parser::ExpressionContext>(0);
}


size_t css3Parser::FunctionalPseudoContext::getRuleIndex() const {
  return css3Parser::RuleFunctionalPseudo;
}

void css3Parser::FunctionalPseudoContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionalPseudo(this);
}

void css3Parser::FunctionalPseudoContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionalPseudo(this);
}

css3Parser::FunctionalPseudoContext* css3Parser::functionalPseudo() {
  FunctionalPseudoContext *_localctx = _tracker.createInstance<FunctionalPseudoContext>(_ctx, getState());
  enterRule(_localctx, 48, css3Parser::RuleFunctionalPseudo);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(470);
    match(css3Parser::Function);
    setState(471);
    ws();
    setState(472);
    expression();
    setState(473);
    match(css3Parser::T__3);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

css3Parser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<css3Parser::WsContext *> css3Parser::ExpressionContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::ExpressionContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}

std::vector<tree::TerminalNode *> css3Parser::ExpressionContext::Plus() {
  return getTokens(css3Parser::Plus);
}

tree::TerminalNode* css3Parser::ExpressionContext::Plus(size_t i) {
  return getToken(css3Parser::Plus, i);
}

std::vector<tree::TerminalNode *> css3Parser::ExpressionContext::Minus() {
  return getTokens(css3Parser::Minus);
}

tree::TerminalNode* css3Parser::ExpressionContext::Minus(size_t i) {
  return getToken(css3Parser::Minus, i);
}

std::vector<tree::TerminalNode *> css3Parser::ExpressionContext::Dimension() {
  return getTokens(css3Parser::Dimension);
}

tree::TerminalNode* css3Parser::ExpressionContext::Dimension(size_t i) {
  return getToken(css3Parser::Dimension, i);
}

std::vector<tree::TerminalNode *> css3Parser::ExpressionContext::UnknownDimension() {
  return getTokens(css3Parser::UnknownDimension);
}

tree::TerminalNode* css3Parser::ExpressionContext::UnknownDimension(size_t i) {
  return getToken(css3Parser::UnknownDimension, i);
}

std::vector<tree::TerminalNode *> css3Parser::ExpressionContext::Number() {
  return getTokens(css3Parser::Number);
}

tree::TerminalNode* css3Parser::ExpressionContext::Number(size_t i) {
  return getToken(css3Parser::Number, i);
}

std::vector<tree::TerminalNode *> css3Parser::ExpressionContext::String() {
  return getTokens(css3Parser::String);
}

tree::TerminalNode* css3Parser::ExpressionContext::String(size_t i) {
  return getToken(css3Parser::String, i);
}

std::vector<css3Parser::IdentContext *> css3Parser::ExpressionContext::ident() {
  return getRuleContexts<css3Parser::IdentContext>();
}

css3Parser::IdentContext* css3Parser::ExpressionContext::ident(size_t i) {
  return getRuleContext<css3Parser::IdentContext>(i);
}


size_t css3Parser::ExpressionContext::getRuleIndex() const {
  return css3Parser::RuleExpression;
}

void css3Parser::ExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpression(this);
}

void css3Parser::ExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpression(this);
}

css3Parser::ExpressionContext* css3Parser::expression() {
  ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 50, css3Parser::RuleExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(485); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(482);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case css3Parser::Plus: {
          setState(475);
          match(css3Parser::Plus);
          break;
        }

        case css3Parser::Minus: {
          setState(476);
          match(css3Parser::Minus);
          break;
        }

        case css3Parser::Dimension: {
          setState(477);
          match(css3Parser::Dimension);
          break;
        }

        case css3Parser::UnknownDimension: {
          setState(478);
          match(css3Parser::UnknownDimension);
          break;
        }

        case css3Parser::Number: {
          setState(479);
          match(css3Parser::Number);
          break;
        }

        case css3Parser::String: {
          setState(480);
          match(css3Parser::String);
          break;
        }

        case css3Parser::MediaOnly:
        case css3Parser::Not:
        case css3Parser::And:
        case css3Parser::Or:
        case css3Parser::From:
        case css3Parser::To:
        case css3Parser::Ident: {
          setState(481);
          ident();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(484);
      ws();
      setState(487); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << css3Parser::MediaOnly)
      | (1ULL << css3Parser::Not)
      | (1ULL << css3Parser::And)
      | (1ULL << css3Parser::Dimension)
      | (1ULL << css3Parser::UnknownDimension)
      | (1ULL << css3Parser::Plus)
      | (1ULL << css3Parser::Minus)
      | (1ULL << css3Parser::Number)
      | (1ULL << css3Parser::String)
      | (1ULL << css3Parser::Or)
      | (1ULL << css3Parser::From)
      | (1ULL << css3Parser::To)
      | (1ULL << css3Parser::Ident))) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NegationContext ------------------------------------------------------------------

css3Parser::NegationContext::NegationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* css3Parser::NegationContext::PseudoNot() {
  return getToken(css3Parser::PseudoNot, 0);
}

std::vector<css3Parser::WsContext *> css3Parser::NegationContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::NegationContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}

css3Parser::NegationArgContext* css3Parser::NegationContext::negationArg() {
  return getRuleContext<css3Parser::NegationArgContext>(0);
}


size_t css3Parser::NegationContext::getRuleIndex() const {
  return css3Parser::RuleNegation;
}

void css3Parser::NegationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNegation(this);
}

void css3Parser::NegationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNegation(this);
}

css3Parser::NegationContext* css3Parser::negation() {
  NegationContext *_localctx = _tracker.createInstance<NegationContext>(_ctx, getState());
  enterRule(_localctx, 52, css3Parser::RuleNegation);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(489);
    match(css3Parser::PseudoNot);
    setState(490);
    ws();
    setState(491);
    negationArg();
    setState(492);
    ws();
    setState(493);
    match(css3Parser::T__3);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NegationArgContext ------------------------------------------------------------------

css3Parser::NegationArgContext::NegationArgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

css3Parser::TypeSelectorContext* css3Parser::NegationArgContext::typeSelector() {
  return getRuleContext<css3Parser::TypeSelectorContext>(0);
}

css3Parser::UniversalContext* css3Parser::NegationArgContext::universal() {
  return getRuleContext<css3Parser::UniversalContext>(0);
}

tree::TerminalNode* css3Parser::NegationArgContext::Hash() {
  return getToken(css3Parser::Hash, 0);
}

css3Parser::ClassNameContext* css3Parser::NegationArgContext::className() {
  return getRuleContext<css3Parser::ClassNameContext>(0);
}

css3Parser::AttribContext* css3Parser::NegationArgContext::attrib() {
  return getRuleContext<css3Parser::AttribContext>(0);
}

css3Parser::PseudoContext* css3Parser::NegationArgContext::pseudo() {
  return getRuleContext<css3Parser::PseudoContext>(0);
}


size_t css3Parser::NegationArgContext::getRuleIndex() const {
  return css3Parser::RuleNegationArg;
}

void css3Parser::NegationArgContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNegationArg(this);
}

void css3Parser::NegationArgContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNegationArg(this);
}

css3Parser::NegationArgContext* css3Parser::negationArg() {
  NegationArgContext *_localctx = _tracker.createInstance<NegationArgContext>(_ctx, getState());
  enterRule(_localctx, 54, css3Parser::RuleNegationArg);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(501);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(495);
      typeSelector();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(496);
      universal();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(497);
      match(css3Parser::Hash);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(498);
      className();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(499);
      attrib();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(500);
      pseudo();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CssoperatorContext ------------------------------------------------------------------

css3Parser::CssoperatorContext::CssoperatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t css3Parser::CssoperatorContext::getRuleIndex() const {
  return css3Parser::RuleCssoperator;
}

void css3Parser::CssoperatorContext::copyFrom(CssoperatorContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- BadOperatorContext ------------------------------------------------------------------

css3Parser::WsContext* css3Parser::BadOperatorContext::ws() {
  return getRuleContext<css3Parser::WsContext>(0);
}

css3Parser::BadOperatorContext::BadOperatorContext(CssoperatorContext *ctx) { copyFrom(ctx); }

void css3Parser::BadOperatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBadOperator(this);
}
void css3Parser::BadOperatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBadOperator(this);
}
//----------------- GoodOperatorContext ------------------------------------------------------------------

css3Parser::WsContext* css3Parser::GoodOperatorContext::ws() {
  return getRuleContext<css3Parser::WsContext>(0);
}

tree::TerminalNode* css3Parser::GoodOperatorContext::Comma() {
  return getToken(css3Parser::Comma, 0);
}

tree::TerminalNode* css3Parser::GoodOperatorContext::Space() {
  return getToken(css3Parser::Space, 0);
}

css3Parser::GoodOperatorContext::GoodOperatorContext(CssoperatorContext *ctx) { copyFrom(ctx); }

void css3Parser::GoodOperatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGoodOperator(this);
}
void css3Parser::GoodOperatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGoodOperator(this);
}
css3Parser::CssoperatorContext* css3Parser::cssoperator() {
  CssoperatorContext *_localctx = _tracker.createInstance<CssoperatorContext>(_ctx, getState());
  enterRule(_localctx, 56, css3Parser::RuleCssoperator);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(511);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case css3Parser::T__12: {
        _localctx = dynamic_cast<CssoperatorContext *>(_tracker.createInstance<css3Parser::GoodOperatorContext>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(503);
        match(css3Parser::T__12);
        setState(504);
        ws();
        break;
      }

      case css3Parser::Comma: {
        _localctx = dynamic_cast<CssoperatorContext *>(_tracker.createInstance<css3Parser::GoodOperatorContext>(_localctx));
        enterOuterAlt(_localctx, 2);
        setState(505);
        match(css3Parser::Comma);
        setState(506);
        ws();
        break;
      }

      case css3Parser::Space: {
        _localctx = dynamic_cast<CssoperatorContext *>(_tracker.createInstance<css3Parser::GoodOperatorContext>(_localctx));
        enterOuterAlt(_localctx, 3);
        setState(507);
        match(css3Parser::Space);
        setState(508);
        ws();
        break;
      }

      case css3Parser::T__10: {
        _localctx = dynamic_cast<CssoperatorContext *>(_tracker.createInstance<css3Parser::BadOperatorContext>(_localctx));
        enterOuterAlt(_localctx, 4);
        setState(509);
        match(css3Parser::T__10);
        setState(510);
        ws();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PropertyContext ------------------------------------------------------------------

css3Parser::PropertyContext::PropertyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t css3Parser::PropertyContext::getRuleIndex() const {
  return css3Parser::RuleProperty;
}

void css3Parser::PropertyContext::copyFrom(PropertyContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- BadPropertyContext ------------------------------------------------------------------

css3Parser::IdentContext* css3Parser::BadPropertyContext::ident() {
  return getRuleContext<css3Parser::IdentContext>(0);
}

css3Parser::BadPropertyContext::BadPropertyContext(PropertyContext *ctx) { copyFrom(ctx); }

void css3Parser::BadPropertyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBadProperty(this);
}
void css3Parser::BadPropertyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBadProperty(this);
}
//----------------- GoodPropertyContext ------------------------------------------------------------------

css3Parser::IdentContext* css3Parser::GoodPropertyContext::ident() {
  return getRuleContext<css3Parser::IdentContext>(0);
}

css3Parser::WsContext* css3Parser::GoodPropertyContext::ws() {
  return getRuleContext<css3Parser::WsContext>(0);
}

tree::TerminalNode* css3Parser::GoodPropertyContext::Variable() {
  return getToken(css3Parser::Variable, 0);
}

css3Parser::GoodPropertyContext::GoodPropertyContext(PropertyContext *ctx) { copyFrom(ctx); }

void css3Parser::GoodPropertyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGoodProperty(this);
}
void css3Parser::GoodPropertyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGoodProperty(this);
}
css3Parser::PropertyContext* css3Parser::property() {
  PropertyContext *_localctx = _tracker.createInstance<PropertyContext>(_ctx, getState());
  enterRule(_localctx, 58, css3Parser::RuleProperty);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(522);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case css3Parser::MediaOnly:
      case css3Parser::Not:
      case css3Parser::And:
      case css3Parser::Or:
      case css3Parser::From:
      case css3Parser::To:
      case css3Parser::Ident: {
        _localctx = dynamic_cast<PropertyContext *>(_tracker.createInstance<css3Parser::GoodPropertyContext>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(513);
        ident();
        setState(514);
        ws();
        break;
      }

      case css3Parser::Variable: {
        _localctx = dynamic_cast<PropertyContext *>(_tracker.createInstance<css3Parser::GoodPropertyContext>(_localctx));
        enterOuterAlt(_localctx, 2);
        setState(516);
        match(css3Parser::Variable);
        setState(517);
        ws();
        break;
      }

      case css3Parser::T__6: {
        _localctx = dynamic_cast<PropertyContext *>(_tracker.createInstance<css3Parser::BadPropertyContext>(_localctx));
        enterOuterAlt(_localctx, 3);
        setState(518);
        match(css3Parser::T__6);
        setState(519);
        ident();
        break;
      }

      case css3Parser::T__13: {
        _localctx = dynamic_cast<PropertyContext *>(_tracker.createInstance<css3Parser::BadPropertyContext>(_localctx));
        enterOuterAlt(_localctx, 4);
        setState(520);
        match(css3Parser::T__13);
        setState(521);
        ident();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RulesetContext ------------------------------------------------------------------

css3Parser::RulesetContext::RulesetContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t css3Parser::RulesetContext::getRuleIndex() const {
  return css3Parser::RuleRuleset;
}

void css3Parser::RulesetContext::copyFrom(RulesetContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- UnknownRulesetContext ------------------------------------------------------------------

std::vector<css3Parser::WsContext *> css3Parser::UnknownRulesetContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::UnknownRulesetContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}

std::vector<css3Parser::AnyContext *> css3Parser::UnknownRulesetContext::any() {
  return getRuleContexts<css3Parser::AnyContext>();
}

css3Parser::AnyContext* css3Parser::UnknownRulesetContext::any(size_t i) {
  return getRuleContext<css3Parser::AnyContext>(i);
}

css3Parser::DeclarationListContext* css3Parser::UnknownRulesetContext::declarationList() {
  return getRuleContext<css3Parser::DeclarationListContext>(0);
}

css3Parser::UnknownRulesetContext::UnknownRulesetContext(RulesetContext *ctx) { copyFrom(ctx); }

void css3Parser::UnknownRulesetContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnknownRuleset(this);
}
void css3Parser::UnknownRulesetContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnknownRuleset(this);
}
//----------------- KnownRulesetContext ------------------------------------------------------------------

css3Parser::SelectorGroupContext* css3Parser::KnownRulesetContext::selectorGroup() {
  return getRuleContext<css3Parser::SelectorGroupContext>(0);
}

std::vector<css3Parser::WsContext *> css3Parser::KnownRulesetContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::KnownRulesetContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}

css3Parser::DeclarationListContext* css3Parser::KnownRulesetContext::declarationList() {
  return getRuleContext<css3Parser::DeclarationListContext>(0);
}

css3Parser::KnownRulesetContext::KnownRulesetContext(RulesetContext *ctx) { copyFrom(ctx); }

void css3Parser::KnownRulesetContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterKnownRuleset(this);
}
void css3Parser::KnownRulesetContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitKnownRuleset(this);
}
css3Parser::RulesetContext* css3Parser::ruleset() {
  RulesetContext *_localctx = _tracker.createInstance<RulesetContext>(_ctx, getState());
  enterRule(_localctx, 60, css3Parser::RuleRuleset);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(547);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 49, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<RulesetContext *>(_tracker.createInstance<css3Parser::KnownRulesetContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(524);
      selectorGroup();
      setState(525);
      match(css3Parser::T__4);
      setState(526);
      ws();
      setState(528);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << css3Parser::T__0)
        | (1ULL << css3Parser::T__6)
        | (1ULL << css3Parser::T__13)
        | (1ULL << css3Parser::MediaOnly)
        | (1ULL << css3Parser::Not)
        | (1ULL << css3Parser::And)
        | (1ULL << css3Parser::Or)
        | (1ULL << css3Parser::From)
        | (1ULL << css3Parser::To)
        | (1ULL << css3Parser::Variable)
        | (1ULL << css3Parser::Ident))) != 0)) {
        setState(527);
        declarationList();
      }
      setState(530);
      match(css3Parser::T__5);
      setState(531);
      ws();
      break;
    }

    case 2: {
      _localctx = dynamic_cast<RulesetContext *>(_tracker.createInstance<css3Parser::UnknownRulesetContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(536);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << css3Parser::T__1)
        | (1ULL << css3Parser::T__2)
        | (1ULL << css3Parser::T__9)
        | (1ULL << css3Parser::Includes)
        | (1ULL << css3Parser::DashMatch)
        | (1ULL << css3Parser::Hash)
        | (1ULL << css3Parser::Percentage)
        | (1ULL << css3Parser::Uri)
        | (1ULL << css3Parser::UnicodeRange)
        | (1ULL << css3Parser::MediaOnly)
        | (1ULL << css3Parser::Not)
        | (1ULL << css3Parser::And)
        | (1ULL << css3Parser::Dimension)
        | (1ULL << css3Parser::UnknownDimension)
        | (1ULL << css3Parser::Plus)
        | (1ULL << css3Parser::Minus)
        | (1ULL << css3Parser::Number)
        | (1ULL << css3Parser::String)
        | (1ULL << css3Parser::Or)
        | (1ULL << css3Parser::From)
        | (1ULL << css3Parser::To)
        | (1ULL << css3Parser::Ident)
        | (1ULL << css3Parser::Function))) != 0)) {
        setState(533);
        any();
        setState(538);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(539);
      match(css3Parser::T__4);
      setState(540);
      ws();
      setState(542);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << css3Parser::T__0)
        | (1ULL << css3Parser::T__6)
        | (1ULL << css3Parser::T__13)
        | (1ULL << css3Parser::MediaOnly)
        | (1ULL << css3Parser::Not)
        | (1ULL << css3Parser::And)
        | (1ULL << css3Parser::Or)
        | (1ULL << css3Parser::From)
        | (1ULL << css3Parser::To)
        | (1ULL << css3Parser::Variable)
        | (1ULL << css3Parser::Ident))) != 0)) {
        setState(541);
        declarationList();
      }
      setState(544);
      match(css3Parser::T__5);
      setState(545);
      ws();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclarationListContext ------------------------------------------------------------------

css3Parser::DeclarationListContext::DeclarationListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<css3Parser::DeclarationContext *> css3Parser::DeclarationListContext::declaration() {
  return getRuleContexts<css3Parser::DeclarationContext>();
}

css3Parser::DeclarationContext* css3Parser::DeclarationListContext::declaration(size_t i) {
  return getRuleContext<css3Parser::DeclarationContext>(i);
}

std::vector<css3Parser::WsContext *> css3Parser::DeclarationListContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::DeclarationListContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}


size_t css3Parser::DeclarationListContext::getRuleIndex() const {
  return css3Parser::RuleDeclarationList;
}

void css3Parser::DeclarationListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDeclarationList(this);
}

void css3Parser::DeclarationListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDeclarationList(this);
}

css3Parser::DeclarationListContext* css3Parser::declarationList() {
  DeclarationListContext *_localctx = _tracker.createInstance<DeclarationListContext>(_ctx, getState());
  enterRule(_localctx, 62, css3Parser::RuleDeclarationList);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(553);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == css3Parser::T__0) {
      setState(549);
      match(css3Parser::T__0);
      setState(550);
      ws();
      setState(555);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(556);
    declaration();
    setState(557);
    ws();
    setState(565);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 52, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(558);
        match(css3Parser::T__0);
        setState(559);
        ws();
        setState(561);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx)) {
        case 1: {
          setState(560);
          declaration();
          break;
        }

        } 
      }
      setState(567);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 52, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclarationContext ------------------------------------------------------------------

css3Parser::DeclarationContext::DeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t css3Parser::DeclarationContext::getRuleIndex() const {
  return css3Parser::RuleDeclaration;
}

void css3Parser::DeclarationContext::copyFrom(DeclarationContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- UnknownDeclarationContext ------------------------------------------------------------------

css3Parser::PropertyContext* css3Parser::UnknownDeclarationContext::property() {
  return getRuleContext<css3Parser::PropertyContext>(0);
}

css3Parser::WsContext* css3Parser::UnknownDeclarationContext::ws() {
  return getRuleContext<css3Parser::WsContext>(0);
}

css3Parser::ValueContext* css3Parser::UnknownDeclarationContext::value() {
  return getRuleContext<css3Parser::ValueContext>(0);
}

css3Parser::UnknownDeclarationContext::UnknownDeclarationContext(DeclarationContext *ctx) { copyFrom(ctx); }

void css3Parser::UnknownDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnknownDeclaration(this);
}
void css3Parser::UnknownDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnknownDeclaration(this);
}
//----------------- KnownDeclarationContext ------------------------------------------------------------------

css3Parser::PropertyContext* css3Parser::KnownDeclarationContext::property() {
  return getRuleContext<css3Parser::PropertyContext>(0);
}

css3Parser::WsContext* css3Parser::KnownDeclarationContext::ws() {
  return getRuleContext<css3Parser::WsContext>(0);
}

css3Parser::ExprContext* css3Parser::KnownDeclarationContext::expr() {
  return getRuleContext<css3Parser::ExprContext>(0);
}

css3Parser::PrioContext* css3Parser::KnownDeclarationContext::prio() {
  return getRuleContext<css3Parser::PrioContext>(0);
}

css3Parser::KnownDeclarationContext::KnownDeclarationContext(DeclarationContext *ctx) { copyFrom(ctx); }

void css3Parser::KnownDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterKnownDeclaration(this);
}
void css3Parser::KnownDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitKnownDeclaration(this);
}
css3Parser::DeclarationContext* css3Parser::declaration() {
  DeclarationContext *_localctx = _tracker.createInstance<DeclarationContext>(_ctx, getState());
  enterRule(_localctx, 64, css3Parser::RuleDeclaration);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(580);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 54, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<DeclarationContext *>(_tracker.createInstance<css3Parser::KnownDeclarationContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(568);
      property();
      setState(569);
      match(css3Parser::T__2);
      setState(570);
      ws();
      setState(571);
      expr();
      setState(573);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == css3Parser::Important) {
        setState(572);
        prio();
      }
      break;
    }

    case 2: {
      _localctx = dynamic_cast<DeclarationContext *>(_tracker.createInstance<css3Parser::UnknownDeclarationContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(575);
      property();
      setState(576);
      match(css3Parser::T__2);
      setState(577);
      ws();
      setState(578);
      value();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrioContext ------------------------------------------------------------------

css3Parser::PrioContext::PrioContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* css3Parser::PrioContext::Important() {
  return getToken(css3Parser::Important, 0);
}

css3Parser::WsContext* css3Parser::PrioContext::ws() {
  return getRuleContext<css3Parser::WsContext>(0);
}


size_t css3Parser::PrioContext::getRuleIndex() const {
  return css3Parser::RulePrio;
}

void css3Parser::PrioContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPrio(this);
}

void css3Parser::PrioContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPrio(this);
}

css3Parser::PrioContext* css3Parser::prio() {
  PrioContext *_localctx = _tracker.createInstance<PrioContext>(_ctx, getState());
  enterRule(_localctx, 66, css3Parser::RulePrio);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(582);
    match(css3Parser::Important);
    setState(583);
    ws();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ValueContext ------------------------------------------------------------------

css3Parser::ValueContext::ValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<css3Parser::AnyContext *> css3Parser::ValueContext::any() {
  return getRuleContexts<css3Parser::AnyContext>();
}

css3Parser::AnyContext* css3Parser::ValueContext::any(size_t i) {
  return getRuleContext<css3Parser::AnyContext>(i);
}

std::vector<css3Parser::BlockContext *> css3Parser::ValueContext::block() {
  return getRuleContexts<css3Parser::BlockContext>();
}

css3Parser::BlockContext* css3Parser::ValueContext::block(size_t i) {
  return getRuleContext<css3Parser::BlockContext>(i);
}

std::vector<css3Parser::AtKeywordContext *> css3Parser::ValueContext::atKeyword() {
  return getRuleContexts<css3Parser::AtKeywordContext>();
}

css3Parser::AtKeywordContext* css3Parser::ValueContext::atKeyword(size_t i) {
  return getRuleContext<css3Parser::AtKeywordContext>(i);
}

std::vector<css3Parser::WsContext *> css3Parser::ValueContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::ValueContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}


size_t css3Parser::ValueContext::getRuleIndex() const {
  return css3Parser::RuleValue;
}

void css3Parser::ValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterValue(this);
}

void css3Parser::ValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitValue(this);
}

css3Parser::ValueContext* css3Parser::value() {
  ValueContext *_localctx = _tracker.createInstance<ValueContext>(_ctx, getState());
  enterRule(_localctx, 68, css3Parser::RuleValue);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(590); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(590);
              _errHandler->sync(this);
              switch (_input->LA(1)) {
                case css3Parser::T__1:
                case css3Parser::T__2:
                case css3Parser::T__9:
                case css3Parser::Includes:
                case css3Parser::DashMatch:
                case css3Parser::Hash:
                case css3Parser::Percentage:
                case css3Parser::Uri:
                case css3Parser::UnicodeRange:
                case css3Parser::MediaOnly:
                case css3Parser::Not:
                case css3Parser::And:
                case css3Parser::Dimension:
                case css3Parser::UnknownDimension:
                case css3Parser::Plus:
                case css3Parser::Minus:
                case css3Parser::Number:
                case css3Parser::String:
                case css3Parser::Or:
                case css3Parser::From:
                case css3Parser::To:
                case css3Parser::Ident:
                case css3Parser::Function: {
                  setState(585);
                  any();
                  break;
                }

                case css3Parser::T__4: {
                  setState(586);
                  block();
                  break;
                }

                case css3Parser::T__14: {
                  setState(587);
                  atKeyword();
                  setState(588);
                  ws();
                  break;
                }

              default:
                throw NoViableAltException(this);
              }
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(592); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 56, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

css3Parser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<css3Parser::TermContext *> css3Parser::ExprContext::term() {
  return getRuleContexts<css3Parser::TermContext>();
}

css3Parser::TermContext* css3Parser::ExprContext::term(size_t i) {
  return getRuleContext<css3Parser::TermContext>(i);
}

std::vector<css3Parser::CssoperatorContext *> css3Parser::ExprContext::cssoperator() {
  return getRuleContexts<css3Parser::CssoperatorContext>();
}

css3Parser::CssoperatorContext* css3Parser::ExprContext::cssoperator(size_t i) {
  return getRuleContext<css3Parser::CssoperatorContext>(i);
}


size_t css3Parser::ExprContext::getRuleIndex() const {
  return css3Parser::RuleExpr;
}

void css3Parser::ExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpr(this);
}

void css3Parser::ExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpr(this);
}

css3Parser::ExprContext* css3Parser::expr() {
  ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, getState());
  enterRule(_localctx, 70, css3Parser::RuleExpr);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(594);
    term();
    setState(601);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 58, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(596);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << css3Parser::T__10)
          | (1ULL << css3Parser::T__12)
          | (1ULL << css3Parser::Space)
          | (1ULL << css3Parser::Comma))) != 0)) {
          setState(595);
          cssoperator();
        }
        setState(598);
        term(); 
      }
      setState(603);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 58, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TermContext ------------------------------------------------------------------

css3Parser::TermContext::TermContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t css3Parser::TermContext::getRuleIndex() const {
  return css3Parser::RuleTerm;
}

void css3Parser::TermContext::copyFrom(TermContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- BadTermContext ------------------------------------------------------------------

css3Parser::DxImageTransformContext* css3Parser::BadTermContext::dxImageTransform() {
  return getRuleContext<css3Parser::DxImageTransformContext>(0);
}

css3Parser::BadTermContext::BadTermContext(TermContext *ctx) { copyFrom(ctx); }

void css3Parser::BadTermContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBadTerm(this);
}
void css3Parser::BadTermContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBadTerm(this);
}
//----------------- KnownTermContext ------------------------------------------------------------------

css3Parser::NumberContext* css3Parser::KnownTermContext::number() {
  return getRuleContext<css3Parser::NumberContext>(0);
}

css3Parser::WsContext* css3Parser::KnownTermContext::ws() {
  return getRuleContext<css3Parser::WsContext>(0);
}

css3Parser::PercentageContext* css3Parser::KnownTermContext::percentage() {
  return getRuleContext<css3Parser::PercentageContext>(0);
}

css3Parser::DimensionContext* css3Parser::KnownTermContext::dimension() {
  return getRuleContext<css3Parser::DimensionContext>(0);
}

tree::TerminalNode* css3Parser::KnownTermContext::String() {
  return getToken(css3Parser::String, 0);
}

tree::TerminalNode* css3Parser::KnownTermContext::UnicodeRange() {
  return getToken(css3Parser::UnicodeRange, 0);
}

css3Parser::IdentContext* css3Parser::KnownTermContext::ident() {
  return getRuleContext<css3Parser::IdentContext>(0);
}

css3Parser::VarContext* css3Parser::KnownTermContext::var() {
  return getRuleContext<css3Parser::VarContext>(0);
}

tree::TerminalNode* css3Parser::KnownTermContext::Uri() {
  return getToken(css3Parser::Uri, 0);
}

css3Parser::HexcolorContext* css3Parser::KnownTermContext::hexcolor() {
  return getRuleContext<css3Parser::HexcolorContext>(0);
}

css3Parser::CalcContext* css3Parser::KnownTermContext::calc() {
  return getRuleContext<css3Parser::CalcContext>(0);
}

css3Parser::FunctionContext* css3Parser::KnownTermContext::function() {
  return getRuleContext<css3Parser::FunctionContext>(0);
}

css3Parser::KnownTermContext::KnownTermContext(TermContext *ctx) { copyFrom(ctx); }

void css3Parser::KnownTermContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterKnownTerm(this);
}
void css3Parser::KnownTermContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitKnownTerm(this);
}
//----------------- UnknownTermContext ------------------------------------------------------------------

css3Parser::UnknownDimensionContext* css3Parser::UnknownTermContext::unknownDimension() {
  return getRuleContext<css3Parser::UnknownDimensionContext>(0);
}

css3Parser::WsContext* css3Parser::UnknownTermContext::ws() {
  return getRuleContext<css3Parser::WsContext>(0);
}

css3Parser::UnknownTermContext::UnknownTermContext(TermContext *ctx) { copyFrom(ctx); }

void css3Parser::UnknownTermContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnknownTerm(this);
}
void css3Parser::UnknownTermContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnknownTerm(this);
}
css3Parser::TermContext* css3Parser::term() {
  TermContext *_localctx = _tracker.createInstance<TermContext>(_ctx, getState());
  enterRule(_localctx, 72, css3Parser::RuleTerm);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(630);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 59, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<TermContext *>(_tracker.createInstance<css3Parser::KnownTermContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(604);
      number();
      setState(605);
      ws();
      break;
    }

    case 2: {
      _localctx = dynamic_cast<TermContext *>(_tracker.createInstance<css3Parser::KnownTermContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(607);
      percentage();
      setState(608);
      ws();
      break;
    }

    case 3: {
      _localctx = dynamic_cast<TermContext *>(_tracker.createInstance<css3Parser::KnownTermContext>(_localctx));
      enterOuterAlt(_localctx, 3);
      setState(610);
      dimension();
      setState(611);
      ws();
      break;
    }

    case 4: {
      _localctx = dynamic_cast<TermContext *>(_tracker.createInstance<css3Parser::KnownTermContext>(_localctx));
      enterOuterAlt(_localctx, 4);
      setState(613);
      match(css3Parser::String);
      setState(614);
      ws();
      break;
    }

    case 5: {
      _localctx = dynamic_cast<TermContext *>(_tracker.createInstance<css3Parser::KnownTermContext>(_localctx));
      enterOuterAlt(_localctx, 5);
      setState(615);
      match(css3Parser::UnicodeRange);
      setState(616);
      ws();
      break;
    }

    case 6: {
      _localctx = dynamic_cast<TermContext *>(_tracker.createInstance<css3Parser::KnownTermContext>(_localctx));
      enterOuterAlt(_localctx, 6);
      setState(617);
      ident();
      setState(618);
      ws();
      break;
    }

    case 7: {
      _localctx = dynamic_cast<TermContext *>(_tracker.createInstance<css3Parser::KnownTermContext>(_localctx));
      enterOuterAlt(_localctx, 7);
      setState(620);
      var();
      break;
    }

    case 8: {
      _localctx = dynamic_cast<TermContext *>(_tracker.createInstance<css3Parser::KnownTermContext>(_localctx));
      enterOuterAlt(_localctx, 8);
      setState(621);
      match(css3Parser::Uri);
      setState(622);
      ws();
      break;
    }

    case 9: {
      _localctx = dynamic_cast<TermContext *>(_tracker.createInstance<css3Parser::KnownTermContext>(_localctx));
      enterOuterAlt(_localctx, 9);
      setState(623);
      hexcolor();
      break;
    }

    case 10: {
      _localctx = dynamic_cast<TermContext *>(_tracker.createInstance<css3Parser::KnownTermContext>(_localctx));
      enterOuterAlt(_localctx, 10);
      setState(624);
      calc();
      break;
    }

    case 11: {
      _localctx = dynamic_cast<TermContext *>(_tracker.createInstance<css3Parser::KnownTermContext>(_localctx));
      enterOuterAlt(_localctx, 11);
      setState(625);
      function();
      break;
    }

    case 12: {
      _localctx = dynamic_cast<TermContext *>(_tracker.createInstance<css3Parser::UnknownTermContext>(_localctx));
      enterOuterAlt(_localctx, 12);
      setState(626);
      unknownDimension();
      setState(627);
      ws();
      break;
    }

    case 13: {
      _localctx = dynamic_cast<TermContext *>(_tracker.createInstance<css3Parser::BadTermContext>(_localctx));
      enterOuterAlt(_localctx, 13);
      setState(629);
      dxImageTransform();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionContext ------------------------------------------------------------------

css3Parser::FunctionContext::FunctionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* css3Parser::FunctionContext::Function() {
  return getToken(css3Parser::Function, 0);
}

std::vector<css3Parser::WsContext *> css3Parser::FunctionContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::FunctionContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}

css3Parser::ExprContext* css3Parser::FunctionContext::expr() {
  return getRuleContext<css3Parser::ExprContext>(0);
}


size_t css3Parser::FunctionContext::getRuleIndex() const {
  return css3Parser::RuleFunction;
}

void css3Parser::FunctionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunction(this);
}

void css3Parser::FunctionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunction(this);
}

css3Parser::FunctionContext* css3Parser::function() {
  FunctionContext *_localctx = _tracker.createInstance<FunctionContext>(_ctx, getState());
  enterRule(_localctx, 74, css3Parser::RuleFunction);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(632);
    match(css3Parser::Function);
    setState(633);
    ws();
    setState(634);
    expr();
    setState(635);
    match(css3Parser::T__3);
    setState(636);
    ws();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DxImageTransformContext ------------------------------------------------------------------

css3Parser::DxImageTransformContext::DxImageTransformContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* css3Parser::DxImageTransformContext::DxImageTransform() {
  return getToken(css3Parser::DxImageTransform, 0);
}

std::vector<css3Parser::WsContext *> css3Parser::DxImageTransformContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::DxImageTransformContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}

css3Parser::ExprContext* css3Parser::DxImageTransformContext::expr() {
  return getRuleContext<css3Parser::ExprContext>(0);
}


size_t css3Parser::DxImageTransformContext::getRuleIndex() const {
  return css3Parser::RuleDxImageTransform;
}

void css3Parser::DxImageTransformContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDxImageTransform(this);
}

void css3Parser::DxImageTransformContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDxImageTransform(this);
}

css3Parser::DxImageTransformContext* css3Parser::dxImageTransform() {
  DxImageTransformContext *_localctx = _tracker.createInstance<DxImageTransformContext>(_ctx, getState());
  enterRule(_localctx, 76, css3Parser::RuleDxImageTransform);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(638);
    match(css3Parser::DxImageTransform);
    setState(639);
    ws();
    setState(640);
    expr();
    setState(641);
    match(css3Parser::T__3);
    setState(642);
    ws();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- HexcolorContext ------------------------------------------------------------------

css3Parser::HexcolorContext::HexcolorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* css3Parser::HexcolorContext::Hash() {
  return getToken(css3Parser::Hash, 0);
}

css3Parser::WsContext* css3Parser::HexcolorContext::ws() {
  return getRuleContext<css3Parser::WsContext>(0);
}


size_t css3Parser::HexcolorContext::getRuleIndex() const {
  return css3Parser::RuleHexcolor;
}

void css3Parser::HexcolorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterHexcolor(this);
}

void css3Parser::HexcolorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitHexcolor(this);
}

css3Parser::HexcolorContext* css3Parser::hexcolor() {
  HexcolorContext *_localctx = _tracker.createInstance<HexcolorContext>(_ctx, getState());
  enterRule(_localctx, 78, css3Parser::RuleHexcolor);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(644);
    match(css3Parser::Hash);
    setState(645);
    ws();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumberContext ------------------------------------------------------------------

css3Parser::NumberContext::NumberContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* css3Parser::NumberContext::Number() {
  return getToken(css3Parser::Number, 0);
}

tree::TerminalNode* css3Parser::NumberContext::Plus() {
  return getToken(css3Parser::Plus, 0);
}

tree::TerminalNode* css3Parser::NumberContext::Minus() {
  return getToken(css3Parser::Minus, 0);
}


size_t css3Parser::NumberContext::getRuleIndex() const {
  return css3Parser::RuleNumber;
}

void css3Parser::NumberContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumber(this);
}

void css3Parser::NumberContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumber(this);
}

css3Parser::NumberContext* css3Parser::number() {
  NumberContext *_localctx = _tracker.createInstance<NumberContext>(_ctx, getState());
  enterRule(_localctx, 80, css3Parser::RuleNumber);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(648);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == css3Parser::Plus

    || _la == css3Parser::Minus) {
      setState(647);
      _la = _input->LA(1);
      if (!(_la == css3Parser::Plus

      || _la == css3Parser::Minus)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
    }
    setState(650);
    match(css3Parser::Number);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PercentageContext ------------------------------------------------------------------

css3Parser::PercentageContext::PercentageContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* css3Parser::PercentageContext::Percentage() {
  return getToken(css3Parser::Percentage, 0);
}

tree::TerminalNode* css3Parser::PercentageContext::Plus() {
  return getToken(css3Parser::Plus, 0);
}

tree::TerminalNode* css3Parser::PercentageContext::Minus() {
  return getToken(css3Parser::Minus, 0);
}


size_t css3Parser::PercentageContext::getRuleIndex() const {
  return css3Parser::RulePercentage;
}

void css3Parser::PercentageContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPercentage(this);
}

void css3Parser::PercentageContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPercentage(this);
}

css3Parser::PercentageContext* css3Parser::percentage() {
  PercentageContext *_localctx = _tracker.createInstance<PercentageContext>(_ctx, getState());
  enterRule(_localctx, 82, css3Parser::RulePercentage);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(653);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == css3Parser::Plus

    || _la == css3Parser::Minus) {
      setState(652);
      _la = _input->LA(1);
      if (!(_la == css3Parser::Plus

      || _la == css3Parser::Minus)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
    }
    setState(655);
    match(css3Parser::Percentage);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DimensionContext ------------------------------------------------------------------

css3Parser::DimensionContext::DimensionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* css3Parser::DimensionContext::Dimension() {
  return getToken(css3Parser::Dimension, 0);
}

tree::TerminalNode* css3Parser::DimensionContext::Plus() {
  return getToken(css3Parser::Plus, 0);
}

tree::TerminalNode* css3Parser::DimensionContext::Minus() {
  return getToken(css3Parser::Minus, 0);
}


size_t css3Parser::DimensionContext::getRuleIndex() const {
  return css3Parser::RuleDimension;
}

void css3Parser::DimensionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDimension(this);
}

void css3Parser::DimensionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDimension(this);
}

css3Parser::DimensionContext* css3Parser::dimension() {
  DimensionContext *_localctx = _tracker.createInstance<DimensionContext>(_ctx, getState());
  enterRule(_localctx, 84, css3Parser::RuleDimension);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(658);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == css3Parser::Plus

    || _la == css3Parser::Minus) {
      setState(657);
      _la = _input->LA(1);
      if (!(_la == css3Parser::Plus

      || _la == css3Parser::Minus)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
    }
    setState(660);
    match(css3Parser::Dimension);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnknownDimensionContext ------------------------------------------------------------------

css3Parser::UnknownDimensionContext::UnknownDimensionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* css3Parser::UnknownDimensionContext::UnknownDimension() {
  return getToken(css3Parser::UnknownDimension, 0);
}

tree::TerminalNode* css3Parser::UnknownDimensionContext::Plus() {
  return getToken(css3Parser::Plus, 0);
}

tree::TerminalNode* css3Parser::UnknownDimensionContext::Minus() {
  return getToken(css3Parser::Minus, 0);
}


size_t css3Parser::UnknownDimensionContext::getRuleIndex() const {
  return css3Parser::RuleUnknownDimension;
}

void css3Parser::UnknownDimensionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnknownDimension(this);
}

void css3Parser::UnknownDimensionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnknownDimension(this);
}

css3Parser::UnknownDimensionContext* css3Parser::unknownDimension() {
  UnknownDimensionContext *_localctx = _tracker.createInstance<UnknownDimensionContext>(_ctx, getState());
  enterRule(_localctx, 86, css3Parser::RuleUnknownDimension);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(663);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == css3Parser::Plus

    || _la == css3Parser::Minus) {
      setState(662);
      _la = _input->LA(1);
      if (!(_la == css3Parser::Plus

      || _la == css3Parser::Minus)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
    }
    setState(665);
    match(css3Parser::UnknownDimension);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AnyContext ------------------------------------------------------------------

css3Parser::AnyContext::AnyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

css3Parser::IdentContext* css3Parser::AnyContext::ident() {
  return getRuleContext<css3Parser::IdentContext>(0);
}

std::vector<css3Parser::WsContext *> css3Parser::AnyContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::AnyContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}

css3Parser::NumberContext* css3Parser::AnyContext::number() {
  return getRuleContext<css3Parser::NumberContext>(0);
}

css3Parser::PercentageContext* css3Parser::AnyContext::percentage() {
  return getRuleContext<css3Parser::PercentageContext>(0);
}

css3Parser::DimensionContext* css3Parser::AnyContext::dimension() {
  return getRuleContext<css3Parser::DimensionContext>(0);
}

css3Parser::UnknownDimensionContext* css3Parser::AnyContext::unknownDimension() {
  return getRuleContext<css3Parser::UnknownDimensionContext>(0);
}

tree::TerminalNode* css3Parser::AnyContext::String() {
  return getToken(css3Parser::String, 0);
}

tree::TerminalNode* css3Parser::AnyContext::Uri() {
  return getToken(css3Parser::Uri, 0);
}

tree::TerminalNode* css3Parser::AnyContext::Hash() {
  return getToken(css3Parser::Hash, 0);
}

tree::TerminalNode* css3Parser::AnyContext::UnicodeRange() {
  return getToken(css3Parser::UnicodeRange, 0);
}

tree::TerminalNode* css3Parser::AnyContext::Includes() {
  return getToken(css3Parser::Includes, 0);
}

tree::TerminalNode* css3Parser::AnyContext::DashMatch() {
  return getToken(css3Parser::DashMatch, 0);
}

tree::TerminalNode* css3Parser::AnyContext::Function() {
  return getToken(css3Parser::Function, 0);
}

std::vector<css3Parser::AnyContext *> css3Parser::AnyContext::any() {
  return getRuleContexts<css3Parser::AnyContext>();
}

css3Parser::AnyContext* css3Parser::AnyContext::any(size_t i) {
  return getRuleContext<css3Parser::AnyContext>(i);
}

std::vector<css3Parser::UnusedContext *> css3Parser::AnyContext::unused() {
  return getRuleContexts<css3Parser::UnusedContext>();
}

css3Parser::UnusedContext* css3Parser::AnyContext::unused(size_t i) {
  return getRuleContext<css3Parser::UnusedContext>(i);
}


size_t css3Parser::AnyContext::getRuleIndex() const {
  return css3Parser::RuleAny;
}

void css3Parser::AnyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAny(this);
}

void css3Parser::AnyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAny(this);
}

css3Parser::AnyContext* css3Parser::any() {
  AnyContext *_localctx = _tracker.createInstance<AnyContext>(_ctx, getState());
  enterRule(_localctx, 88, css3Parser::RuleAny);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(732);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 70, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(667);
      ident();
      setState(668);
      ws();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(670);
      number();
      setState(671);
      ws();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(673);
      percentage();
      setState(674);
      ws();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(676);
      dimension();
      setState(677);
      ws();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(679);
      unknownDimension();
      setState(680);
      ws();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(682);
      match(css3Parser::String);
      setState(683);
      ws();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(684);
      match(css3Parser::Uri);
      setState(685);
      ws();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(686);
      match(css3Parser::Hash);
      setState(687);
      ws();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(688);
      match(css3Parser::UnicodeRange);
      setState(689);
      ws();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(690);
      match(css3Parser::Includes);
      setState(691);
      ws();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(692);
      match(css3Parser::DashMatch);
      setState(693);
      ws();
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(694);
      match(css3Parser::T__2);
      setState(695);
      ws();
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(696);
      match(css3Parser::Function);
      setState(697);
      ws();
      setState(702);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << css3Parser::T__0)
        | (1ULL << css3Parser::T__1)
        | (1ULL << css3Parser::T__2)
        | (1ULL << css3Parser::T__4)
        | (1ULL << css3Parser::T__9)
        | (1ULL << css3Parser::T__14)
        | (1ULL << css3Parser::Cdo)
        | (1ULL << css3Parser::Cdc)
        | (1ULL << css3Parser::Includes)
        | (1ULL << css3Parser::DashMatch)
        | (1ULL << css3Parser::Hash)
        | (1ULL << css3Parser::Percentage)
        | (1ULL << css3Parser::Uri)
        | (1ULL << css3Parser::UnicodeRange)
        | (1ULL << css3Parser::MediaOnly)
        | (1ULL << css3Parser::Not)
        | (1ULL << css3Parser::And)
        | (1ULL << css3Parser::Dimension)
        | (1ULL << css3Parser::UnknownDimension)
        | (1ULL << css3Parser::Plus)
        | (1ULL << css3Parser::Minus)
        | (1ULL << css3Parser::Number)
        | (1ULL << css3Parser::String)
        | (1ULL << css3Parser::Or)
        | (1ULL << css3Parser::From)
        | (1ULL << css3Parser::To)
        | (1ULL << css3Parser::Ident)
        | (1ULL << css3Parser::Function))) != 0)) {
        setState(700);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case css3Parser::T__1:
          case css3Parser::T__2:
          case css3Parser::T__9:
          case css3Parser::Includes:
          case css3Parser::DashMatch:
          case css3Parser::Hash:
          case css3Parser::Percentage:
          case css3Parser::Uri:
          case css3Parser::UnicodeRange:
          case css3Parser::MediaOnly:
          case css3Parser::Not:
          case css3Parser::And:
          case css3Parser::Dimension:
          case css3Parser::UnknownDimension:
          case css3Parser::Plus:
          case css3Parser::Minus:
          case css3Parser::Number:
          case css3Parser::String:
          case css3Parser::Or:
          case css3Parser::From:
          case css3Parser::To:
          case css3Parser::Ident:
          case css3Parser::Function: {
            setState(698);
            any();
            break;
          }

          case css3Parser::T__0:
          case css3Parser::T__4:
          case css3Parser::T__14:
          case css3Parser::Cdo:
          case css3Parser::Cdc: {
            setState(699);
            unused();
            break;
          }

        default:
          throw NoViableAltException(this);
        }
        setState(704);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(705);
      match(css3Parser::T__3);
      setState(706);
      ws();
      break;
    }

    case 14: {
      enterOuterAlt(_localctx, 14);
      setState(708);
      match(css3Parser::T__1);
      setState(709);
      ws();
      setState(714);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << css3Parser::T__0)
        | (1ULL << css3Parser::T__1)
        | (1ULL << css3Parser::T__2)
        | (1ULL << css3Parser::T__4)
        | (1ULL << css3Parser::T__9)
        | (1ULL << css3Parser::T__14)
        | (1ULL << css3Parser::Cdo)
        | (1ULL << css3Parser::Cdc)
        | (1ULL << css3Parser::Includes)
        | (1ULL << css3Parser::DashMatch)
        | (1ULL << css3Parser::Hash)
        | (1ULL << css3Parser::Percentage)
        | (1ULL << css3Parser::Uri)
        | (1ULL << css3Parser::UnicodeRange)
        | (1ULL << css3Parser::MediaOnly)
        | (1ULL << css3Parser::Not)
        | (1ULL << css3Parser::And)
        | (1ULL << css3Parser::Dimension)
        | (1ULL << css3Parser::UnknownDimension)
        | (1ULL << css3Parser::Plus)
        | (1ULL << css3Parser::Minus)
        | (1ULL << css3Parser::Number)
        | (1ULL << css3Parser::String)
        | (1ULL << css3Parser::Or)
        | (1ULL << css3Parser::From)
        | (1ULL << css3Parser::To)
        | (1ULL << css3Parser::Ident)
        | (1ULL << css3Parser::Function))) != 0)) {
        setState(712);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case css3Parser::T__1:
          case css3Parser::T__2:
          case css3Parser::T__9:
          case css3Parser::Includes:
          case css3Parser::DashMatch:
          case css3Parser::Hash:
          case css3Parser::Percentage:
          case css3Parser::Uri:
          case css3Parser::UnicodeRange:
          case css3Parser::MediaOnly:
          case css3Parser::Not:
          case css3Parser::And:
          case css3Parser::Dimension:
          case css3Parser::UnknownDimension:
          case css3Parser::Plus:
          case css3Parser::Minus:
          case css3Parser::Number:
          case css3Parser::String:
          case css3Parser::Or:
          case css3Parser::From:
          case css3Parser::To:
          case css3Parser::Ident:
          case css3Parser::Function: {
            setState(710);
            any();
            break;
          }

          case css3Parser::T__0:
          case css3Parser::T__4:
          case css3Parser::T__14:
          case css3Parser::Cdo:
          case css3Parser::Cdc: {
            setState(711);
            unused();
            break;
          }

        default:
          throw NoViableAltException(this);
        }
        setState(716);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(717);
      match(css3Parser::T__3);
      setState(718);
      ws();
      break;
    }

    case 15: {
      enterOuterAlt(_localctx, 15);
      setState(720);
      match(css3Parser::T__9);
      setState(721);
      ws();
      setState(726);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << css3Parser::T__0)
        | (1ULL << css3Parser::T__1)
        | (1ULL << css3Parser::T__2)
        | (1ULL << css3Parser::T__4)
        | (1ULL << css3Parser::T__9)
        | (1ULL << css3Parser::T__14)
        | (1ULL << css3Parser::Cdo)
        | (1ULL << css3Parser::Cdc)
        | (1ULL << css3Parser::Includes)
        | (1ULL << css3Parser::DashMatch)
        | (1ULL << css3Parser::Hash)
        | (1ULL << css3Parser::Percentage)
        | (1ULL << css3Parser::Uri)
        | (1ULL << css3Parser::UnicodeRange)
        | (1ULL << css3Parser::MediaOnly)
        | (1ULL << css3Parser::Not)
        | (1ULL << css3Parser::And)
        | (1ULL << css3Parser::Dimension)
        | (1ULL << css3Parser::UnknownDimension)
        | (1ULL << css3Parser::Plus)
        | (1ULL << css3Parser::Minus)
        | (1ULL << css3Parser::Number)
        | (1ULL << css3Parser::String)
        | (1ULL << css3Parser::Or)
        | (1ULL << css3Parser::From)
        | (1ULL << css3Parser::To)
        | (1ULL << css3Parser::Ident)
        | (1ULL << css3Parser::Function))) != 0)) {
        setState(724);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case css3Parser::T__1:
          case css3Parser::T__2:
          case css3Parser::T__9:
          case css3Parser::Includes:
          case css3Parser::DashMatch:
          case css3Parser::Hash:
          case css3Parser::Percentage:
          case css3Parser::Uri:
          case css3Parser::UnicodeRange:
          case css3Parser::MediaOnly:
          case css3Parser::Not:
          case css3Parser::And:
          case css3Parser::Dimension:
          case css3Parser::UnknownDimension:
          case css3Parser::Plus:
          case css3Parser::Minus:
          case css3Parser::Number:
          case css3Parser::String:
          case css3Parser::Or:
          case css3Parser::From:
          case css3Parser::To:
          case css3Parser::Ident:
          case css3Parser::Function: {
            setState(722);
            any();
            break;
          }

          case css3Parser::T__0:
          case css3Parser::T__4:
          case css3Parser::T__14:
          case css3Parser::Cdo:
          case css3Parser::Cdc: {
            setState(723);
            unused();
            break;
          }

        default:
          throw NoViableAltException(this);
        }
        setState(728);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(729);
      match(css3Parser::T__11);
      setState(730);
      ws();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AtRuleContext ------------------------------------------------------------------

css3Parser::AtRuleContext::AtRuleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t css3Parser::AtRuleContext::getRuleIndex() const {
  return css3Parser::RuleAtRule;
}

void css3Parser::AtRuleContext::copyFrom(AtRuleContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- UnknownAtRuleContext ------------------------------------------------------------------

css3Parser::AtKeywordContext* css3Parser::UnknownAtRuleContext::atKeyword() {
  return getRuleContext<css3Parser::AtKeywordContext>(0);
}

std::vector<css3Parser::WsContext *> css3Parser::UnknownAtRuleContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::UnknownAtRuleContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}

css3Parser::BlockContext* css3Parser::UnknownAtRuleContext::block() {
  return getRuleContext<css3Parser::BlockContext>(0);
}

std::vector<css3Parser::AnyContext *> css3Parser::UnknownAtRuleContext::any() {
  return getRuleContexts<css3Parser::AnyContext>();
}

css3Parser::AnyContext* css3Parser::UnknownAtRuleContext::any(size_t i) {
  return getRuleContext<css3Parser::AnyContext>(i);
}

css3Parser::UnknownAtRuleContext::UnknownAtRuleContext(AtRuleContext *ctx) { copyFrom(ctx); }

void css3Parser::UnknownAtRuleContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnknownAtRule(this);
}
void css3Parser::UnknownAtRuleContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnknownAtRule(this);
}
css3Parser::AtRuleContext* css3Parser::atRule() {
  AtRuleContext *_localctx = _tracker.createInstance<AtRuleContext>(_ctx, getState());
  enterRule(_localctx, 90, css3Parser::RuleAtRule);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    _localctx = dynamic_cast<AtRuleContext *>(_tracker.createInstance<css3Parser::UnknownAtRuleContext>(_localctx));
    enterOuterAlt(_localctx, 1);
    setState(734);
    atKeyword();
    setState(735);
    ws();
    setState(739);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << css3Parser::T__1)
      | (1ULL << css3Parser::T__2)
      | (1ULL << css3Parser::T__9)
      | (1ULL << css3Parser::Includes)
      | (1ULL << css3Parser::DashMatch)
      | (1ULL << css3Parser::Hash)
      | (1ULL << css3Parser::Percentage)
      | (1ULL << css3Parser::Uri)
      | (1ULL << css3Parser::UnicodeRange)
      | (1ULL << css3Parser::MediaOnly)
      | (1ULL << css3Parser::Not)
      | (1ULL << css3Parser::And)
      | (1ULL << css3Parser::Dimension)
      | (1ULL << css3Parser::UnknownDimension)
      | (1ULL << css3Parser::Plus)
      | (1ULL << css3Parser::Minus)
      | (1ULL << css3Parser::Number)
      | (1ULL << css3Parser::String)
      | (1ULL << css3Parser::Or)
      | (1ULL << css3Parser::From)
      | (1ULL << css3Parser::To)
      | (1ULL << css3Parser::Ident)
      | (1ULL << css3Parser::Function))) != 0)) {
      setState(736);
      any();
      setState(741);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(745);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case css3Parser::T__4: {
        setState(742);
        block();
        break;
      }

      case css3Parser::T__0: {
        setState(743);
        match(css3Parser::T__0);
        setState(744);
        ws();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AtKeywordContext ------------------------------------------------------------------

css3Parser::AtKeywordContext::AtKeywordContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

css3Parser::IdentContext* css3Parser::AtKeywordContext::ident() {
  return getRuleContext<css3Parser::IdentContext>(0);
}


size_t css3Parser::AtKeywordContext::getRuleIndex() const {
  return css3Parser::RuleAtKeyword;
}

void css3Parser::AtKeywordContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAtKeyword(this);
}

void css3Parser::AtKeywordContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAtKeyword(this);
}

css3Parser::AtKeywordContext* css3Parser::atKeyword() {
  AtKeywordContext *_localctx = _tracker.createInstance<AtKeywordContext>(_ctx, getState());
  enterRule(_localctx, 92, css3Parser::RuleAtKeyword);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(747);
    match(css3Parser::T__14);
    setState(748);
    ident();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnusedContext ------------------------------------------------------------------

css3Parser::UnusedContext::UnusedContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

css3Parser::BlockContext* css3Parser::UnusedContext::block() {
  return getRuleContext<css3Parser::BlockContext>(0);
}

css3Parser::AtKeywordContext* css3Parser::UnusedContext::atKeyword() {
  return getRuleContext<css3Parser::AtKeywordContext>(0);
}

css3Parser::WsContext* css3Parser::UnusedContext::ws() {
  return getRuleContext<css3Parser::WsContext>(0);
}

tree::TerminalNode* css3Parser::UnusedContext::Cdo() {
  return getToken(css3Parser::Cdo, 0);
}

tree::TerminalNode* css3Parser::UnusedContext::Cdc() {
  return getToken(css3Parser::Cdc, 0);
}


size_t css3Parser::UnusedContext::getRuleIndex() const {
  return css3Parser::RuleUnused;
}

void css3Parser::UnusedContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnused(this);
}

void css3Parser::UnusedContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnused(this);
}

css3Parser::UnusedContext* css3Parser::unused() {
  UnusedContext *_localctx = _tracker.createInstance<UnusedContext>(_ctx, getState());
  enterRule(_localctx, 94, css3Parser::RuleUnused);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(760);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case css3Parser::T__4: {
        enterOuterAlt(_localctx, 1);
        setState(750);
        block();
        break;
      }

      case css3Parser::T__14: {
        enterOuterAlt(_localctx, 2);
        setState(751);
        atKeyword();
        setState(752);
        ws();
        break;
      }

      case css3Parser::T__0: {
        enterOuterAlt(_localctx, 3);
        setState(754);
        match(css3Parser::T__0);
        setState(755);
        ws();
        break;
      }

      case css3Parser::Cdo: {
        enterOuterAlt(_localctx, 4);
        setState(756);
        match(css3Parser::Cdo);
        setState(757);
        ws();
        break;
      }

      case css3Parser::Cdc: {
        enterOuterAlt(_localctx, 5);
        setState(758);
        match(css3Parser::Cdc);
        setState(759);
        ws();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

css3Parser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<css3Parser::WsContext *> css3Parser::BlockContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::BlockContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}

std::vector<css3Parser::DeclarationListContext *> css3Parser::BlockContext::declarationList() {
  return getRuleContexts<css3Parser::DeclarationListContext>();
}

css3Parser::DeclarationListContext* css3Parser::BlockContext::declarationList(size_t i) {
  return getRuleContext<css3Parser::DeclarationListContext>(i);
}

std::vector<css3Parser::NestedStatementContext *> css3Parser::BlockContext::nestedStatement() {
  return getRuleContexts<css3Parser::NestedStatementContext>();
}

css3Parser::NestedStatementContext* css3Parser::BlockContext::nestedStatement(size_t i) {
  return getRuleContext<css3Parser::NestedStatementContext>(i);
}

std::vector<css3Parser::AnyContext *> css3Parser::BlockContext::any() {
  return getRuleContexts<css3Parser::AnyContext>();
}

css3Parser::AnyContext* css3Parser::BlockContext::any(size_t i) {
  return getRuleContext<css3Parser::AnyContext>(i);
}

std::vector<css3Parser::BlockContext *> css3Parser::BlockContext::block() {
  return getRuleContexts<css3Parser::BlockContext>();
}

css3Parser::BlockContext* css3Parser::BlockContext::block(size_t i) {
  return getRuleContext<css3Parser::BlockContext>(i);
}

std::vector<css3Parser::AtKeywordContext *> css3Parser::BlockContext::atKeyword() {
  return getRuleContexts<css3Parser::AtKeywordContext>();
}

css3Parser::AtKeywordContext* css3Parser::BlockContext::atKeyword(size_t i) {
  return getRuleContext<css3Parser::AtKeywordContext>(i);
}


size_t css3Parser::BlockContext::getRuleIndex() const {
  return css3Parser::RuleBlock;
}

void css3Parser::BlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlock(this);
}

void css3Parser::BlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlock(this);
}

css3Parser::BlockContext* css3Parser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 96, css3Parser::RuleBlock);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(762);
    match(css3Parser::T__4);
    setState(763);
    ws();
    setState(775);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << css3Parser::T__0)
      | (1ULL << css3Parser::T__1)
      | (1ULL << css3Parser::T__2)
      | (1ULL << css3Parser::T__4)
      | (1ULL << css3Parser::T__6)
      | (1ULL << css3Parser::T__7)
      | (1ULL << css3Parser::T__8)
      | (1ULL << css3Parser::T__9)
      | (1ULL << css3Parser::T__13)
      | (1ULL << css3Parser::T__14)
      | (1ULL << css3Parser::Includes)
      | (1ULL << css3Parser::DashMatch)
      | (1ULL << css3Parser::Hash)
      | (1ULL << css3Parser::Page)
      | (1ULL << css3Parser::Media)
      | (1ULL << css3Parser::Percentage)
      | (1ULL << css3Parser::Uri)
      | (1ULL << css3Parser::UnicodeRange)
      | (1ULL << css3Parser::MediaOnly)
      | (1ULL << css3Parser::Not)
      | (1ULL << css3Parser::And)
      | (1ULL << css3Parser::Dimension)
      | (1ULL << css3Parser::UnknownDimension)
      | (1ULL << css3Parser::Plus)
      | (1ULL << css3Parser::Minus)
      | (1ULL << css3Parser::PseudoNot)
      | (1ULL << css3Parser::Number)
      | (1ULL << css3Parser::String)
      | (1ULL << css3Parser::FontFace)
      | (1ULL << css3Parser::Supports)
      | (1ULL << css3Parser::Or)
      | (1ULL << css3Parser::Keyframes)
      | (1ULL << css3Parser::From)
      | (1ULL << css3Parser::To)
      | (1ULL << css3Parser::Viewport)
      | (1ULL << css3Parser::CounterStyle)
      | (1ULL << css3Parser::FontFeatureValues)
      | (1ULL << css3Parser::Variable)
      | (1ULL << css3Parser::Ident)
      | (1ULL << css3Parser::Function))) != 0)) {
      setState(773);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 74, _ctx)) {
      case 1: {
        setState(764);
        declarationList();
        break;
      }

      case 2: {
        setState(765);
        nestedStatement();
        break;
      }

      case 3: {
        setState(766);
        any();
        break;
      }

      case 4: {
        setState(767);
        block();
        break;
      }

      case 5: {
        setState(768);
        atKeyword();
        setState(769);
        ws();
        break;
      }

      case 6: {
        setState(771);
        match(css3Parser::T__0);
        setState(772);
        ws();
        break;
      }

      }
      setState(777);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(778);
    match(css3Parser::T__5);
    setState(779);
    ws();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NestedStatementContext ------------------------------------------------------------------

css3Parser::NestedStatementContext::NestedStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

css3Parser::RulesetContext* css3Parser::NestedStatementContext::ruleset() {
  return getRuleContext<css3Parser::RulesetContext>(0);
}

css3Parser::MediaContext* css3Parser::NestedStatementContext::media() {
  return getRuleContext<css3Parser::MediaContext>(0);
}

css3Parser::PageContext* css3Parser::NestedStatementContext::page() {
  return getRuleContext<css3Parser::PageContext>(0);
}

css3Parser::FontFaceRuleContext* css3Parser::NestedStatementContext::fontFaceRule() {
  return getRuleContext<css3Parser::FontFaceRuleContext>(0);
}

css3Parser::KeyframesRuleContext* css3Parser::NestedStatementContext::keyframesRule() {
  return getRuleContext<css3Parser::KeyframesRuleContext>(0);
}

css3Parser::SupportsRuleContext* css3Parser::NestedStatementContext::supportsRule() {
  return getRuleContext<css3Parser::SupportsRuleContext>(0);
}

css3Parser::ViewportContext* css3Parser::NestedStatementContext::viewport() {
  return getRuleContext<css3Parser::ViewportContext>(0);
}

css3Parser::CounterStyleContext* css3Parser::NestedStatementContext::counterStyle() {
  return getRuleContext<css3Parser::CounterStyleContext>(0);
}

css3Parser::FontFeatureValuesRuleContext* css3Parser::NestedStatementContext::fontFeatureValuesRule() {
  return getRuleContext<css3Parser::FontFeatureValuesRuleContext>(0);
}

css3Parser::AtRuleContext* css3Parser::NestedStatementContext::atRule() {
  return getRuleContext<css3Parser::AtRuleContext>(0);
}


size_t css3Parser::NestedStatementContext::getRuleIndex() const {
  return css3Parser::RuleNestedStatement;
}

void css3Parser::NestedStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNestedStatement(this);
}

void css3Parser::NestedStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNestedStatement(this);
}

css3Parser::NestedStatementContext* css3Parser::nestedStatement() {
  NestedStatementContext *_localctx = _tracker.createInstance<NestedStatementContext>(_ctx, getState());
  enterRule(_localctx, 98, css3Parser::RuleNestedStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(791);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case css3Parser::T__1:
      case css3Parser::T__2:
      case css3Parser::T__4:
      case css3Parser::T__6:
      case css3Parser::T__7:
      case css3Parser::T__8:
      case css3Parser::T__9:
      case css3Parser::Includes:
      case css3Parser::DashMatch:
      case css3Parser::Hash:
      case css3Parser::Percentage:
      case css3Parser::Uri:
      case css3Parser::UnicodeRange:
      case css3Parser::MediaOnly:
      case css3Parser::Not:
      case css3Parser::And:
      case css3Parser::Dimension:
      case css3Parser::UnknownDimension:
      case css3Parser::Plus:
      case css3Parser::Minus:
      case css3Parser::PseudoNot:
      case css3Parser::Number:
      case css3Parser::String:
      case css3Parser::Or:
      case css3Parser::From:
      case css3Parser::To:
      case css3Parser::Ident:
      case css3Parser::Function: {
        enterOuterAlt(_localctx, 1);
        setState(781);
        ruleset();
        break;
      }

      case css3Parser::Media: {
        enterOuterAlt(_localctx, 2);
        setState(782);
        media();
        break;
      }

      case css3Parser::Page: {
        enterOuterAlt(_localctx, 3);
        setState(783);
        page();
        break;
      }

      case css3Parser::FontFace: {
        enterOuterAlt(_localctx, 4);
        setState(784);
        fontFaceRule();
        break;
      }

      case css3Parser::Keyframes: {
        enterOuterAlt(_localctx, 5);
        setState(785);
        keyframesRule();
        break;
      }

      case css3Parser::Supports: {
        enterOuterAlt(_localctx, 6);
        setState(786);
        supportsRule();
        break;
      }

      case css3Parser::Viewport: {
        enterOuterAlt(_localctx, 7);
        setState(787);
        viewport();
        break;
      }

      case css3Parser::CounterStyle: {
        enterOuterAlt(_localctx, 8);
        setState(788);
        counterStyle();
        break;
      }

      case css3Parser::FontFeatureValues: {
        enterOuterAlt(_localctx, 9);
        setState(789);
        fontFeatureValuesRule();
        break;
      }

      case css3Parser::T__14: {
        enterOuterAlt(_localctx, 10);
        setState(790);
        atRule();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GroupRuleBodyContext ------------------------------------------------------------------

css3Parser::GroupRuleBodyContext::GroupRuleBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<css3Parser::WsContext *> css3Parser::GroupRuleBodyContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::GroupRuleBodyContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}

std::vector<css3Parser::NestedStatementContext *> css3Parser::GroupRuleBodyContext::nestedStatement() {
  return getRuleContexts<css3Parser::NestedStatementContext>();
}

css3Parser::NestedStatementContext* css3Parser::GroupRuleBodyContext::nestedStatement(size_t i) {
  return getRuleContext<css3Parser::NestedStatementContext>(i);
}


size_t css3Parser::GroupRuleBodyContext::getRuleIndex() const {
  return css3Parser::RuleGroupRuleBody;
}

void css3Parser::GroupRuleBodyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGroupRuleBody(this);
}

void css3Parser::GroupRuleBodyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGroupRuleBody(this);
}

css3Parser::GroupRuleBodyContext* css3Parser::groupRuleBody() {
  GroupRuleBodyContext *_localctx = _tracker.createInstance<GroupRuleBodyContext>(_ctx, getState());
  enterRule(_localctx, 100, css3Parser::RuleGroupRuleBody);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(793);
    match(css3Parser::T__4);
    setState(794);
    ws();
    setState(798);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << css3Parser::T__1)
      | (1ULL << css3Parser::T__2)
      | (1ULL << css3Parser::T__4)
      | (1ULL << css3Parser::T__6)
      | (1ULL << css3Parser::T__7)
      | (1ULL << css3Parser::T__8)
      | (1ULL << css3Parser::T__9)
      | (1ULL << css3Parser::T__14)
      | (1ULL << css3Parser::Includes)
      | (1ULL << css3Parser::DashMatch)
      | (1ULL << css3Parser::Hash)
      | (1ULL << css3Parser::Page)
      | (1ULL << css3Parser::Media)
      | (1ULL << css3Parser::Percentage)
      | (1ULL << css3Parser::Uri)
      | (1ULL << css3Parser::UnicodeRange)
      | (1ULL << css3Parser::MediaOnly)
      | (1ULL << css3Parser::Not)
      | (1ULL << css3Parser::And)
      | (1ULL << css3Parser::Dimension)
      | (1ULL << css3Parser::UnknownDimension)
      | (1ULL << css3Parser::Plus)
      | (1ULL << css3Parser::Minus)
      | (1ULL << css3Parser::PseudoNot)
      | (1ULL << css3Parser::Number)
      | (1ULL << css3Parser::String)
      | (1ULL << css3Parser::FontFace)
      | (1ULL << css3Parser::Supports)
      | (1ULL << css3Parser::Or)
      | (1ULL << css3Parser::Keyframes)
      | (1ULL << css3Parser::From)
      | (1ULL << css3Parser::To)
      | (1ULL << css3Parser::Viewport)
      | (1ULL << css3Parser::CounterStyle)
      | (1ULL << css3Parser::FontFeatureValues)
      | (1ULL << css3Parser::Ident)
      | (1ULL << css3Parser::Function))) != 0)) {
      setState(795);
      nestedStatement();
      setState(800);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(801);
    match(css3Parser::T__5);
    setState(802);
    ws();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SupportsRuleContext ------------------------------------------------------------------

css3Parser::SupportsRuleContext::SupportsRuleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* css3Parser::SupportsRuleContext::Supports() {
  return getToken(css3Parser::Supports, 0);
}

std::vector<css3Parser::WsContext *> css3Parser::SupportsRuleContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::SupportsRuleContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}

css3Parser::SupportsConditionContext* css3Parser::SupportsRuleContext::supportsCondition() {
  return getRuleContext<css3Parser::SupportsConditionContext>(0);
}

css3Parser::GroupRuleBodyContext* css3Parser::SupportsRuleContext::groupRuleBody() {
  return getRuleContext<css3Parser::GroupRuleBodyContext>(0);
}


size_t css3Parser::SupportsRuleContext::getRuleIndex() const {
  return css3Parser::RuleSupportsRule;
}

void css3Parser::SupportsRuleContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSupportsRule(this);
}

void css3Parser::SupportsRuleContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSupportsRule(this);
}

css3Parser::SupportsRuleContext* css3Parser::supportsRule() {
  SupportsRuleContext *_localctx = _tracker.createInstance<SupportsRuleContext>(_ctx, getState());
  enterRule(_localctx, 102, css3Parser::RuleSupportsRule);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(804);
    match(css3Parser::Supports);
    setState(805);
    ws();
    setState(806);
    supportsCondition();
    setState(807);
    ws();
    setState(808);
    groupRuleBody();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SupportsConditionContext ------------------------------------------------------------------

css3Parser::SupportsConditionContext::SupportsConditionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

css3Parser::SupportsNegationContext* css3Parser::SupportsConditionContext::supportsNegation() {
  return getRuleContext<css3Parser::SupportsNegationContext>(0);
}

css3Parser::SupportsConjunctionContext* css3Parser::SupportsConditionContext::supportsConjunction() {
  return getRuleContext<css3Parser::SupportsConjunctionContext>(0);
}

css3Parser::SupportsDisjunctionContext* css3Parser::SupportsConditionContext::supportsDisjunction() {
  return getRuleContext<css3Parser::SupportsDisjunctionContext>(0);
}

css3Parser::SupportsConditionInParensContext* css3Parser::SupportsConditionContext::supportsConditionInParens() {
  return getRuleContext<css3Parser::SupportsConditionInParensContext>(0);
}


size_t css3Parser::SupportsConditionContext::getRuleIndex() const {
  return css3Parser::RuleSupportsCondition;
}

void css3Parser::SupportsConditionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSupportsCondition(this);
}

void css3Parser::SupportsConditionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSupportsCondition(this);
}

css3Parser::SupportsConditionContext* css3Parser::supportsCondition() {
  SupportsConditionContext *_localctx = _tracker.createInstance<SupportsConditionContext>(_ctx, getState());
  enterRule(_localctx, 104, css3Parser::RuleSupportsCondition);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(814);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 78, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(810);
      supportsNegation();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(811);
      supportsConjunction();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(812);
      supportsDisjunction();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(813);
      supportsConditionInParens();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SupportsConditionInParensContext ------------------------------------------------------------------

css3Parser::SupportsConditionInParensContext::SupportsConditionInParensContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<css3Parser::WsContext *> css3Parser::SupportsConditionInParensContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::SupportsConditionInParensContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}

css3Parser::SupportsConditionContext* css3Parser::SupportsConditionInParensContext::supportsCondition() {
  return getRuleContext<css3Parser::SupportsConditionContext>(0);
}

css3Parser::SupportsDeclarationConditionContext* css3Parser::SupportsConditionInParensContext::supportsDeclarationCondition() {
  return getRuleContext<css3Parser::SupportsDeclarationConditionContext>(0);
}

css3Parser::GeneralEnclosedContext* css3Parser::SupportsConditionInParensContext::generalEnclosed() {
  return getRuleContext<css3Parser::GeneralEnclosedContext>(0);
}


size_t css3Parser::SupportsConditionInParensContext::getRuleIndex() const {
  return css3Parser::RuleSupportsConditionInParens;
}

void css3Parser::SupportsConditionInParensContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSupportsConditionInParens(this);
}

void css3Parser::SupportsConditionInParensContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSupportsConditionInParens(this);
}

css3Parser::SupportsConditionInParensContext* css3Parser::supportsConditionInParens() {
  SupportsConditionInParensContext *_localctx = _tracker.createInstance<SupportsConditionInParensContext>(_ctx, getState());
  enterRule(_localctx, 106, css3Parser::RuleSupportsConditionInParens);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(824);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 79, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(816);
      match(css3Parser::T__1);
      setState(817);
      ws();
      setState(818);
      supportsCondition();
      setState(819);
      ws();
      setState(820);
      match(css3Parser::T__3);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(822);
      supportsDeclarationCondition();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(823);
      generalEnclosed();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SupportsNegationContext ------------------------------------------------------------------

css3Parser::SupportsNegationContext::SupportsNegationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* css3Parser::SupportsNegationContext::Not() {
  return getToken(css3Parser::Not, 0);
}

std::vector<css3Parser::WsContext *> css3Parser::SupportsNegationContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::SupportsNegationContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}

tree::TerminalNode* css3Parser::SupportsNegationContext::Space() {
  return getToken(css3Parser::Space, 0);
}

css3Parser::SupportsConditionInParensContext* css3Parser::SupportsNegationContext::supportsConditionInParens() {
  return getRuleContext<css3Parser::SupportsConditionInParensContext>(0);
}


size_t css3Parser::SupportsNegationContext::getRuleIndex() const {
  return css3Parser::RuleSupportsNegation;
}

void css3Parser::SupportsNegationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSupportsNegation(this);
}

void css3Parser::SupportsNegationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSupportsNegation(this);
}

css3Parser::SupportsNegationContext* css3Parser::supportsNegation() {
  SupportsNegationContext *_localctx = _tracker.createInstance<SupportsNegationContext>(_ctx, getState());
  enterRule(_localctx, 108, css3Parser::RuleSupportsNegation);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(826);
    match(css3Parser::Not);
    setState(827);
    ws();
    setState(828);
    match(css3Parser::Space);
    setState(829);
    ws();
    setState(830);
    supportsConditionInParens();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SupportsConjunctionContext ------------------------------------------------------------------

css3Parser::SupportsConjunctionContext::SupportsConjunctionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<css3Parser::SupportsConditionInParensContext *> css3Parser::SupportsConjunctionContext::supportsConditionInParens() {
  return getRuleContexts<css3Parser::SupportsConditionInParensContext>();
}

css3Parser::SupportsConditionInParensContext* css3Parser::SupportsConjunctionContext::supportsConditionInParens(size_t i) {
  return getRuleContext<css3Parser::SupportsConditionInParensContext>(i);
}

std::vector<css3Parser::WsContext *> css3Parser::SupportsConjunctionContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::SupportsConjunctionContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}

std::vector<tree::TerminalNode *> css3Parser::SupportsConjunctionContext::Space() {
  return getTokens(css3Parser::Space);
}

tree::TerminalNode* css3Parser::SupportsConjunctionContext::Space(size_t i) {
  return getToken(css3Parser::Space, i);
}

std::vector<tree::TerminalNode *> css3Parser::SupportsConjunctionContext::And() {
  return getTokens(css3Parser::And);
}

tree::TerminalNode* css3Parser::SupportsConjunctionContext::And(size_t i) {
  return getToken(css3Parser::And, i);
}


size_t css3Parser::SupportsConjunctionContext::getRuleIndex() const {
  return css3Parser::RuleSupportsConjunction;
}

void css3Parser::SupportsConjunctionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSupportsConjunction(this);
}

void css3Parser::SupportsConjunctionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSupportsConjunction(this);
}

css3Parser::SupportsConjunctionContext* css3Parser::supportsConjunction() {
  SupportsConjunctionContext *_localctx = _tracker.createInstance<SupportsConjunctionContext>(_ctx, getState());
  enterRule(_localctx, 110, css3Parser::RuleSupportsConjunction);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(832);
    supportsConditionInParens();
    setState(842); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(833);
              ws();
              setState(834);
              match(css3Parser::Space);
              setState(835);
              ws();
              setState(836);
              match(css3Parser::And);
              setState(837);
              ws();
              setState(838);
              match(css3Parser::Space);
              setState(839);
              ws();
              setState(840);
              supportsConditionInParens();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(844); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 80, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SupportsDisjunctionContext ------------------------------------------------------------------

css3Parser::SupportsDisjunctionContext::SupportsDisjunctionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<css3Parser::SupportsConditionInParensContext *> css3Parser::SupportsDisjunctionContext::supportsConditionInParens() {
  return getRuleContexts<css3Parser::SupportsConditionInParensContext>();
}

css3Parser::SupportsConditionInParensContext* css3Parser::SupportsDisjunctionContext::supportsConditionInParens(size_t i) {
  return getRuleContext<css3Parser::SupportsConditionInParensContext>(i);
}

std::vector<css3Parser::WsContext *> css3Parser::SupportsDisjunctionContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::SupportsDisjunctionContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}

std::vector<tree::TerminalNode *> css3Parser::SupportsDisjunctionContext::Space() {
  return getTokens(css3Parser::Space);
}

tree::TerminalNode* css3Parser::SupportsDisjunctionContext::Space(size_t i) {
  return getToken(css3Parser::Space, i);
}

std::vector<tree::TerminalNode *> css3Parser::SupportsDisjunctionContext::Or() {
  return getTokens(css3Parser::Or);
}

tree::TerminalNode* css3Parser::SupportsDisjunctionContext::Or(size_t i) {
  return getToken(css3Parser::Or, i);
}


size_t css3Parser::SupportsDisjunctionContext::getRuleIndex() const {
  return css3Parser::RuleSupportsDisjunction;
}

void css3Parser::SupportsDisjunctionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSupportsDisjunction(this);
}

void css3Parser::SupportsDisjunctionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSupportsDisjunction(this);
}

css3Parser::SupportsDisjunctionContext* css3Parser::supportsDisjunction() {
  SupportsDisjunctionContext *_localctx = _tracker.createInstance<SupportsDisjunctionContext>(_ctx, getState());
  enterRule(_localctx, 112, css3Parser::RuleSupportsDisjunction);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(846);
    supportsConditionInParens();
    setState(856); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(847);
              ws();
              setState(848);
              match(css3Parser::Space);
              setState(849);
              ws();
              setState(850);
              match(css3Parser::Or);
              setState(851);
              ws();
              setState(852);
              match(css3Parser::Space);
              setState(853);
              ws();
              setState(854);
              supportsConditionInParens();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(858); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 81, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SupportsDeclarationConditionContext ------------------------------------------------------------------

css3Parser::SupportsDeclarationConditionContext::SupportsDeclarationConditionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

css3Parser::WsContext* css3Parser::SupportsDeclarationConditionContext::ws() {
  return getRuleContext<css3Parser::WsContext>(0);
}

css3Parser::DeclarationContext* css3Parser::SupportsDeclarationConditionContext::declaration() {
  return getRuleContext<css3Parser::DeclarationContext>(0);
}


size_t css3Parser::SupportsDeclarationConditionContext::getRuleIndex() const {
  return css3Parser::RuleSupportsDeclarationCondition;
}

void css3Parser::SupportsDeclarationConditionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSupportsDeclarationCondition(this);
}

void css3Parser::SupportsDeclarationConditionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSupportsDeclarationCondition(this);
}

css3Parser::SupportsDeclarationConditionContext* css3Parser::supportsDeclarationCondition() {
  SupportsDeclarationConditionContext *_localctx = _tracker.createInstance<SupportsDeclarationConditionContext>(_ctx, getState());
  enterRule(_localctx, 114, css3Parser::RuleSupportsDeclarationCondition);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(860);
    match(css3Parser::T__1);
    setState(861);
    ws();
    setState(862);
    declaration();
    setState(863);
    match(css3Parser::T__3);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GeneralEnclosedContext ------------------------------------------------------------------

css3Parser::GeneralEnclosedContext::GeneralEnclosedContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* css3Parser::GeneralEnclosedContext::Function() {
  return getToken(css3Parser::Function, 0);
}

std::vector<css3Parser::AnyContext *> css3Parser::GeneralEnclosedContext::any() {
  return getRuleContexts<css3Parser::AnyContext>();
}

css3Parser::AnyContext* css3Parser::GeneralEnclosedContext::any(size_t i) {
  return getRuleContext<css3Parser::AnyContext>(i);
}

std::vector<css3Parser::UnusedContext *> css3Parser::GeneralEnclosedContext::unused() {
  return getRuleContexts<css3Parser::UnusedContext>();
}

css3Parser::UnusedContext* css3Parser::GeneralEnclosedContext::unused(size_t i) {
  return getRuleContext<css3Parser::UnusedContext>(i);
}


size_t css3Parser::GeneralEnclosedContext::getRuleIndex() const {
  return css3Parser::RuleGeneralEnclosed;
}

void css3Parser::GeneralEnclosedContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGeneralEnclosed(this);
}

void css3Parser::GeneralEnclosedContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGeneralEnclosed(this);
}

css3Parser::GeneralEnclosedContext* css3Parser::generalEnclosed() {
  GeneralEnclosedContext *_localctx = _tracker.createInstance<GeneralEnclosedContext>(_ctx, getState());
  enterRule(_localctx, 116, css3Parser::RuleGeneralEnclosed);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(865);
    _la = _input->LA(1);
    if (!(_la == css3Parser::T__1

    || _la == css3Parser::Function)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(870);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << css3Parser::T__0)
      | (1ULL << css3Parser::T__1)
      | (1ULL << css3Parser::T__2)
      | (1ULL << css3Parser::T__4)
      | (1ULL << css3Parser::T__9)
      | (1ULL << css3Parser::T__14)
      | (1ULL << css3Parser::Cdo)
      | (1ULL << css3Parser::Cdc)
      | (1ULL << css3Parser::Includes)
      | (1ULL << css3Parser::DashMatch)
      | (1ULL << css3Parser::Hash)
      | (1ULL << css3Parser::Percentage)
      | (1ULL << css3Parser::Uri)
      | (1ULL << css3Parser::UnicodeRange)
      | (1ULL << css3Parser::MediaOnly)
      | (1ULL << css3Parser::Not)
      | (1ULL << css3Parser::And)
      | (1ULL << css3Parser::Dimension)
      | (1ULL << css3Parser::UnknownDimension)
      | (1ULL << css3Parser::Plus)
      | (1ULL << css3Parser::Minus)
      | (1ULL << css3Parser::Number)
      | (1ULL << css3Parser::String)
      | (1ULL << css3Parser::Or)
      | (1ULL << css3Parser::From)
      | (1ULL << css3Parser::To)
      | (1ULL << css3Parser::Ident)
      | (1ULL << css3Parser::Function))) != 0)) {
      setState(868);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case css3Parser::T__1:
        case css3Parser::T__2:
        case css3Parser::T__9:
        case css3Parser::Includes:
        case css3Parser::DashMatch:
        case css3Parser::Hash:
        case css3Parser::Percentage:
        case css3Parser::Uri:
        case css3Parser::UnicodeRange:
        case css3Parser::MediaOnly:
        case css3Parser::Not:
        case css3Parser::And:
        case css3Parser::Dimension:
        case css3Parser::UnknownDimension:
        case css3Parser::Plus:
        case css3Parser::Minus:
        case css3Parser::Number:
        case css3Parser::String:
        case css3Parser::Or:
        case css3Parser::From:
        case css3Parser::To:
        case css3Parser::Ident:
        case css3Parser::Function: {
          setState(866);
          any();
          break;
        }

        case css3Parser::T__0:
        case css3Parser::T__4:
        case css3Parser::T__14:
        case css3Parser::Cdo:
        case css3Parser::Cdc: {
          setState(867);
          unused();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(872);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(873);
    match(css3Parser::T__3);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarContext ------------------------------------------------------------------

css3Parser::VarContext::VarContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* css3Parser::VarContext::Var() {
  return getToken(css3Parser::Var, 0);
}

std::vector<css3Parser::WsContext *> css3Parser::VarContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::VarContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}

tree::TerminalNode* css3Parser::VarContext::Variable() {
  return getToken(css3Parser::Variable, 0);
}


size_t css3Parser::VarContext::getRuleIndex() const {
  return css3Parser::RuleVar;
}

void css3Parser::VarContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVar(this);
}

void css3Parser::VarContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVar(this);
}

css3Parser::VarContext* css3Parser::var() {
  VarContext *_localctx = _tracker.createInstance<VarContext>(_ctx, getState());
  enterRule(_localctx, 118, css3Parser::RuleVar);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(875);
    match(css3Parser::Var);
    setState(876);
    ws();
    setState(877);
    match(css3Parser::Variable);
    setState(878);
    ws();
    setState(879);
    match(css3Parser::T__3);
    setState(880);
    ws();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CalcContext ------------------------------------------------------------------

css3Parser::CalcContext::CalcContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* css3Parser::CalcContext::Calc() {
  return getToken(css3Parser::Calc, 0);
}

std::vector<css3Parser::WsContext *> css3Parser::CalcContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::CalcContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}

css3Parser::CalcSumContext* css3Parser::CalcContext::calcSum() {
  return getRuleContext<css3Parser::CalcSumContext>(0);
}


size_t css3Parser::CalcContext::getRuleIndex() const {
  return css3Parser::RuleCalc;
}

void css3Parser::CalcContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCalc(this);
}

void css3Parser::CalcContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCalc(this);
}

css3Parser::CalcContext* css3Parser::calc() {
  CalcContext *_localctx = _tracker.createInstance<CalcContext>(_ctx, getState());
  enterRule(_localctx, 120, css3Parser::RuleCalc);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(882);
    match(css3Parser::Calc);
    setState(883);
    ws();
    setState(884);
    calcSum();
    setState(885);
    match(css3Parser::T__3);
    setState(886);
    ws();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CalcSumContext ------------------------------------------------------------------

css3Parser::CalcSumContext::CalcSumContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<css3Parser::CalcProductContext *> css3Parser::CalcSumContext::calcProduct() {
  return getRuleContexts<css3Parser::CalcProductContext>();
}

css3Parser::CalcProductContext* css3Parser::CalcSumContext::calcProduct(size_t i) {
  return getRuleContext<css3Parser::CalcProductContext>(i);
}

std::vector<tree::TerminalNode *> css3Parser::CalcSumContext::Space() {
  return getTokens(css3Parser::Space);
}

tree::TerminalNode* css3Parser::CalcSumContext::Space(size_t i) {
  return getToken(css3Parser::Space, i);
}

std::vector<css3Parser::WsContext *> css3Parser::CalcSumContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::CalcSumContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}

std::vector<tree::TerminalNode *> css3Parser::CalcSumContext::Plus() {
  return getTokens(css3Parser::Plus);
}

tree::TerminalNode* css3Parser::CalcSumContext::Plus(size_t i) {
  return getToken(css3Parser::Plus, i);
}

std::vector<tree::TerminalNode *> css3Parser::CalcSumContext::Minus() {
  return getTokens(css3Parser::Minus);
}

tree::TerminalNode* css3Parser::CalcSumContext::Minus(size_t i) {
  return getToken(css3Parser::Minus, i);
}


size_t css3Parser::CalcSumContext::getRuleIndex() const {
  return css3Parser::RuleCalcSum;
}

void css3Parser::CalcSumContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCalcSum(this);
}

void css3Parser::CalcSumContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCalcSum(this);
}

css3Parser::CalcSumContext* css3Parser::calcSum() {
  CalcSumContext *_localctx = _tracker.createInstance<CalcSumContext>(_ctx, getState());
  enterRule(_localctx, 122, css3Parser::RuleCalcSum);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(888);
    calcProduct();
    setState(899);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == css3Parser::Space) {
      setState(889);
      match(css3Parser::Space);
      setState(890);
      ws();
      setState(891);
      _la = _input->LA(1);
      if (!(_la == css3Parser::Plus

      || _la == css3Parser::Minus)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(892);
      ws();
      setState(893);
      match(css3Parser::Space);
      setState(894);
      ws();
      setState(895);
      calcProduct();
      setState(901);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CalcProductContext ------------------------------------------------------------------

css3Parser::CalcProductContext::CalcProductContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<css3Parser::CalcValueContext *> css3Parser::CalcProductContext::calcValue() {
  return getRuleContexts<css3Parser::CalcValueContext>();
}

css3Parser::CalcValueContext* css3Parser::CalcProductContext::calcValue(size_t i) {
  return getRuleContext<css3Parser::CalcValueContext>(i);
}

std::vector<css3Parser::WsContext *> css3Parser::CalcProductContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::CalcProductContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}

std::vector<css3Parser::NumberContext *> css3Parser::CalcProductContext::number() {
  return getRuleContexts<css3Parser::NumberContext>();
}

css3Parser::NumberContext* css3Parser::CalcProductContext::number(size_t i) {
  return getRuleContext<css3Parser::NumberContext>(i);
}


size_t css3Parser::CalcProductContext::getRuleIndex() const {
  return css3Parser::RuleCalcProduct;
}

void css3Parser::CalcProductContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCalcProduct(this);
}

void css3Parser::CalcProductContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCalcProduct(this);
}

css3Parser::CalcProductContext* css3Parser::calcProduct() {
  CalcProductContext *_localctx = _tracker.createInstance<CalcProductContext>(_ctx, getState());
  enterRule(_localctx, 124, css3Parser::RuleCalcProduct);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(902);
    calcValue();
    setState(914);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == css3Parser::T__6

    || _la == css3Parser::T__12) {
      setState(912);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case css3Parser::T__6: {
          setState(903);
          match(css3Parser::T__6);
          setState(904);
          ws();
          setState(905);
          calcValue();
          break;
        }

        case css3Parser::T__12: {
          setState(907);
          match(css3Parser::T__12);
          setState(908);
          ws();
          setState(909);
          number();
          setState(910);
          ws();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(916);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CalcValueContext ------------------------------------------------------------------

css3Parser::CalcValueContext::CalcValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

css3Parser::NumberContext* css3Parser::CalcValueContext::number() {
  return getRuleContext<css3Parser::NumberContext>(0);
}

std::vector<css3Parser::WsContext *> css3Parser::CalcValueContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::CalcValueContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}

css3Parser::DimensionContext* css3Parser::CalcValueContext::dimension() {
  return getRuleContext<css3Parser::DimensionContext>(0);
}

css3Parser::UnknownDimensionContext* css3Parser::CalcValueContext::unknownDimension() {
  return getRuleContext<css3Parser::UnknownDimensionContext>(0);
}

css3Parser::PercentageContext* css3Parser::CalcValueContext::percentage() {
  return getRuleContext<css3Parser::PercentageContext>(0);
}

css3Parser::CalcSumContext* css3Parser::CalcValueContext::calcSum() {
  return getRuleContext<css3Parser::CalcSumContext>(0);
}


size_t css3Parser::CalcValueContext::getRuleIndex() const {
  return css3Parser::RuleCalcValue;
}

void css3Parser::CalcValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCalcValue(this);
}

void css3Parser::CalcValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCalcValue(this);
}

css3Parser::CalcValueContext* css3Parser::calcValue() {
  CalcValueContext *_localctx = _tracker.createInstance<CalcValueContext>(_ctx, getState());
  enterRule(_localctx, 126, css3Parser::RuleCalcValue);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(935);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 87, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(917);
      number();
      setState(918);
      ws();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(920);
      dimension();
      setState(921);
      ws();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(923);
      unknownDimension();
      setState(924);
      ws();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(926);
      percentage();
      setState(927);
      ws();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(929);
      match(css3Parser::T__1);
      setState(930);
      ws();
      setState(931);
      calcSum();
      setState(932);
      match(css3Parser::T__3);
      setState(933);
      ws();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FontFaceRuleContext ------------------------------------------------------------------

css3Parser::FontFaceRuleContext::FontFaceRuleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* css3Parser::FontFaceRuleContext::FontFace() {
  return getToken(css3Parser::FontFace, 0);
}

std::vector<css3Parser::WsContext *> css3Parser::FontFaceRuleContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::FontFaceRuleContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}

std::vector<css3Parser::FontFaceDeclarationContext *> css3Parser::FontFaceRuleContext::fontFaceDeclaration() {
  return getRuleContexts<css3Parser::FontFaceDeclarationContext>();
}

css3Parser::FontFaceDeclarationContext* css3Parser::FontFaceRuleContext::fontFaceDeclaration(size_t i) {
  return getRuleContext<css3Parser::FontFaceDeclarationContext>(i);
}


size_t css3Parser::FontFaceRuleContext::getRuleIndex() const {
  return css3Parser::RuleFontFaceRule;
}

void css3Parser::FontFaceRuleContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFontFaceRule(this);
}

void css3Parser::FontFaceRuleContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFontFaceRule(this);
}

css3Parser::FontFaceRuleContext* css3Parser::fontFaceRule() {
  FontFaceRuleContext *_localctx = _tracker.createInstance<FontFaceRuleContext>(_ctx, getState());
  enterRule(_localctx, 128, css3Parser::RuleFontFaceRule);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(937);
    match(css3Parser::FontFace);
    setState(938);
    ws();
    setState(939);
    match(css3Parser::T__4);
    setState(940);
    ws();
    setState(942);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << css3Parser::T__6)
      | (1ULL << css3Parser::T__13)
      | (1ULL << css3Parser::MediaOnly)
      | (1ULL << css3Parser::Not)
      | (1ULL << css3Parser::And)
      | (1ULL << css3Parser::Or)
      | (1ULL << css3Parser::From)
      | (1ULL << css3Parser::To)
      | (1ULL << css3Parser::Variable)
      | (1ULL << css3Parser::Ident))) != 0)) {
      setState(941);
      fontFaceDeclaration();
    }
    setState(951);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == css3Parser::T__0) {
      setState(944);
      match(css3Parser::T__0);
      setState(945);
      ws();
      setState(947);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << css3Parser::T__6)
        | (1ULL << css3Parser::T__13)
        | (1ULL << css3Parser::MediaOnly)
        | (1ULL << css3Parser::Not)
        | (1ULL << css3Parser::And)
        | (1ULL << css3Parser::Or)
        | (1ULL << css3Parser::From)
        | (1ULL << css3Parser::To)
        | (1ULL << css3Parser::Variable)
        | (1ULL << css3Parser::Ident))) != 0)) {
        setState(946);
        fontFaceDeclaration();
      }
      setState(953);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(954);
    match(css3Parser::T__5);
    setState(955);
    ws();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FontFaceDeclarationContext ------------------------------------------------------------------

css3Parser::FontFaceDeclarationContext::FontFaceDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t css3Parser::FontFaceDeclarationContext::getRuleIndex() const {
  return css3Parser::RuleFontFaceDeclaration;
}

void css3Parser::FontFaceDeclarationContext::copyFrom(FontFaceDeclarationContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- KnownFontFaceDeclarationContext ------------------------------------------------------------------

css3Parser::PropertyContext* css3Parser::KnownFontFaceDeclarationContext::property() {
  return getRuleContext<css3Parser::PropertyContext>(0);
}

css3Parser::WsContext* css3Parser::KnownFontFaceDeclarationContext::ws() {
  return getRuleContext<css3Parser::WsContext>(0);
}

css3Parser::ExprContext* css3Parser::KnownFontFaceDeclarationContext::expr() {
  return getRuleContext<css3Parser::ExprContext>(0);
}

css3Parser::KnownFontFaceDeclarationContext::KnownFontFaceDeclarationContext(FontFaceDeclarationContext *ctx) { copyFrom(ctx); }

void css3Parser::KnownFontFaceDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterKnownFontFaceDeclaration(this);
}
void css3Parser::KnownFontFaceDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitKnownFontFaceDeclaration(this);
}
//----------------- UnknownFontFaceDeclarationContext ------------------------------------------------------------------

css3Parser::PropertyContext* css3Parser::UnknownFontFaceDeclarationContext::property() {
  return getRuleContext<css3Parser::PropertyContext>(0);
}

css3Parser::WsContext* css3Parser::UnknownFontFaceDeclarationContext::ws() {
  return getRuleContext<css3Parser::WsContext>(0);
}

css3Parser::ValueContext* css3Parser::UnknownFontFaceDeclarationContext::value() {
  return getRuleContext<css3Parser::ValueContext>(0);
}

css3Parser::UnknownFontFaceDeclarationContext::UnknownFontFaceDeclarationContext(FontFaceDeclarationContext *ctx) { copyFrom(ctx); }

void css3Parser::UnknownFontFaceDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnknownFontFaceDeclaration(this);
}
void css3Parser::UnknownFontFaceDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnknownFontFaceDeclaration(this);
}
css3Parser::FontFaceDeclarationContext* css3Parser::fontFaceDeclaration() {
  FontFaceDeclarationContext *_localctx = _tracker.createInstance<FontFaceDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 130, css3Parser::RuleFontFaceDeclaration);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(967);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 91, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<FontFaceDeclarationContext *>(_tracker.createInstance<css3Parser::KnownFontFaceDeclarationContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(957);
      property();
      setState(958);
      match(css3Parser::T__2);
      setState(959);
      ws();
      setState(960);
      expr();
      break;
    }

    case 2: {
      _localctx = dynamic_cast<FontFaceDeclarationContext *>(_tracker.createInstance<css3Parser::UnknownFontFaceDeclarationContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(962);
      property();
      setState(963);
      match(css3Parser::T__2);
      setState(964);
      ws();
      setState(965);
      value();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- KeyframesRuleContext ------------------------------------------------------------------

css3Parser::KeyframesRuleContext::KeyframesRuleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* css3Parser::KeyframesRuleContext::Keyframes() {
  return getToken(css3Parser::Keyframes, 0);
}

std::vector<css3Parser::WsContext *> css3Parser::KeyframesRuleContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::KeyframesRuleContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}

tree::TerminalNode* css3Parser::KeyframesRuleContext::Space() {
  return getToken(css3Parser::Space, 0);
}

css3Parser::IdentContext* css3Parser::KeyframesRuleContext::ident() {
  return getRuleContext<css3Parser::IdentContext>(0);
}

css3Parser::KeyframesBlocksContext* css3Parser::KeyframesRuleContext::keyframesBlocks() {
  return getRuleContext<css3Parser::KeyframesBlocksContext>(0);
}


size_t css3Parser::KeyframesRuleContext::getRuleIndex() const {
  return css3Parser::RuleKeyframesRule;
}

void css3Parser::KeyframesRuleContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterKeyframesRule(this);
}

void css3Parser::KeyframesRuleContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitKeyframesRule(this);
}

css3Parser::KeyframesRuleContext* css3Parser::keyframesRule() {
  KeyframesRuleContext *_localctx = _tracker.createInstance<KeyframesRuleContext>(_ctx, getState());
  enterRule(_localctx, 132, css3Parser::RuleKeyframesRule);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(969);
    match(css3Parser::Keyframes);
    setState(970);
    ws();
    setState(971);
    match(css3Parser::Space);
    setState(972);
    ws();
    setState(973);
    ident();
    setState(974);
    ws();
    setState(975);
    match(css3Parser::T__4);
    setState(976);
    ws();
    setState(977);
    keyframesBlocks();
    setState(978);
    match(css3Parser::T__5);
    setState(979);
    ws();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- KeyframesBlocksContext ------------------------------------------------------------------

css3Parser::KeyframesBlocksContext::KeyframesBlocksContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<css3Parser::KeyframeSelectorContext *> css3Parser::KeyframesBlocksContext::keyframeSelector() {
  return getRuleContexts<css3Parser::KeyframeSelectorContext>();
}

css3Parser::KeyframeSelectorContext* css3Parser::KeyframesBlocksContext::keyframeSelector(size_t i) {
  return getRuleContext<css3Parser::KeyframeSelectorContext>(i);
}

std::vector<css3Parser::WsContext *> css3Parser::KeyframesBlocksContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::KeyframesBlocksContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}

std::vector<css3Parser::DeclarationListContext *> css3Parser::KeyframesBlocksContext::declarationList() {
  return getRuleContexts<css3Parser::DeclarationListContext>();
}

css3Parser::DeclarationListContext* css3Parser::KeyframesBlocksContext::declarationList(size_t i) {
  return getRuleContext<css3Parser::DeclarationListContext>(i);
}


size_t css3Parser::KeyframesBlocksContext::getRuleIndex() const {
  return css3Parser::RuleKeyframesBlocks;
}

void css3Parser::KeyframesBlocksContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterKeyframesBlocks(this);
}

void css3Parser::KeyframesBlocksContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitKeyframesBlocks(this);
}

css3Parser::KeyframesBlocksContext* css3Parser::keyframesBlocks() {
  KeyframesBlocksContext *_localctx = _tracker.createInstance<KeyframesBlocksContext>(_ctx, getState());
  enterRule(_localctx, 134, css3Parser::RuleKeyframesBlocks);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(992);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << css3Parser::Percentage)
      | (1ULL << css3Parser::From)
      | (1ULL << css3Parser::To))) != 0)) {
      setState(981);
      keyframeSelector();
      setState(982);
      match(css3Parser::T__4);
      setState(983);
      ws();
      setState(985);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << css3Parser::T__0)
        | (1ULL << css3Parser::T__6)
        | (1ULL << css3Parser::T__13)
        | (1ULL << css3Parser::MediaOnly)
        | (1ULL << css3Parser::Not)
        | (1ULL << css3Parser::And)
        | (1ULL << css3Parser::Or)
        | (1ULL << css3Parser::From)
        | (1ULL << css3Parser::To)
        | (1ULL << css3Parser::Variable)
        | (1ULL << css3Parser::Ident))) != 0)) {
        setState(984);
        declarationList();
      }
      setState(987);
      match(css3Parser::T__5);
      setState(988);
      ws();
      setState(994);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- KeyframeSelectorContext ------------------------------------------------------------------

css3Parser::KeyframeSelectorContext::KeyframeSelectorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<css3Parser::WsContext *> css3Parser::KeyframeSelectorContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::KeyframeSelectorContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}

std::vector<tree::TerminalNode *> css3Parser::KeyframeSelectorContext::From() {
  return getTokens(css3Parser::From);
}

tree::TerminalNode* css3Parser::KeyframeSelectorContext::From(size_t i) {
  return getToken(css3Parser::From, i);
}

std::vector<tree::TerminalNode *> css3Parser::KeyframeSelectorContext::To() {
  return getTokens(css3Parser::To);
}

tree::TerminalNode* css3Parser::KeyframeSelectorContext::To(size_t i) {
  return getToken(css3Parser::To, i);
}

std::vector<tree::TerminalNode *> css3Parser::KeyframeSelectorContext::Percentage() {
  return getTokens(css3Parser::Percentage);
}

tree::TerminalNode* css3Parser::KeyframeSelectorContext::Percentage(size_t i) {
  return getToken(css3Parser::Percentage, i);
}

std::vector<tree::TerminalNode *> css3Parser::KeyframeSelectorContext::Comma() {
  return getTokens(css3Parser::Comma);
}

tree::TerminalNode* css3Parser::KeyframeSelectorContext::Comma(size_t i) {
  return getToken(css3Parser::Comma, i);
}


size_t css3Parser::KeyframeSelectorContext::getRuleIndex() const {
  return css3Parser::RuleKeyframeSelector;
}

void css3Parser::KeyframeSelectorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterKeyframeSelector(this);
}

void css3Parser::KeyframeSelectorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitKeyframeSelector(this);
}

css3Parser::KeyframeSelectorContext* css3Parser::keyframeSelector() {
  KeyframeSelectorContext *_localctx = _tracker.createInstance<KeyframeSelectorContext>(_ctx, getState());
  enterRule(_localctx, 136, css3Parser::RuleKeyframeSelector);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(995);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << css3Parser::Percentage)
      | (1ULL << css3Parser::From)
      | (1ULL << css3Parser::To))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(996);
    ws();
    setState(1004);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == css3Parser::Comma) {
      setState(997);
      match(css3Parser::Comma);
      setState(998);
      ws();
      setState(999);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << css3Parser::Percentage)
        | (1ULL << css3Parser::From)
        | (1ULL << css3Parser::To))) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(1000);
      ws();
      setState(1006);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ViewportContext ------------------------------------------------------------------

css3Parser::ViewportContext::ViewportContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* css3Parser::ViewportContext::Viewport() {
  return getToken(css3Parser::Viewport, 0);
}

std::vector<css3Parser::WsContext *> css3Parser::ViewportContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::ViewportContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}

css3Parser::DeclarationListContext* css3Parser::ViewportContext::declarationList() {
  return getRuleContext<css3Parser::DeclarationListContext>(0);
}


size_t css3Parser::ViewportContext::getRuleIndex() const {
  return css3Parser::RuleViewport;
}

void css3Parser::ViewportContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterViewport(this);
}

void css3Parser::ViewportContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitViewport(this);
}

css3Parser::ViewportContext* css3Parser::viewport() {
  ViewportContext *_localctx = _tracker.createInstance<ViewportContext>(_ctx, getState());
  enterRule(_localctx, 138, css3Parser::RuleViewport);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1007);
    match(css3Parser::Viewport);
    setState(1008);
    ws();
    setState(1009);
    match(css3Parser::T__4);
    setState(1010);
    ws();
    setState(1012);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << css3Parser::T__0)
      | (1ULL << css3Parser::T__6)
      | (1ULL << css3Parser::T__13)
      | (1ULL << css3Parser::MediaOnly)
      | (1ULL << css3Parser::Not)
      | (1ULL << css3Parser::And)
      | (1ULL << css3Parser::Or)
      | (1ULL << css3Parser::From)
      | (1ULL << css3Parser::To)
      | (1ULL << css3Parser::Variable)
      | (1ULL << css3Parser::Ident))) != 0)) {
      setState(1011);
      declarationList();
    }
    setState(1014);
    match(css3Parser::T__5);
    setState(1015);
    ws();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CounterStyleContext ------------------------------------------------------------------

css3Parser::CounterStyleContext::CounterStyleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* css3Parser::CounterStyleContext::CounterStyle() {
  return getToken(css3Parser::CounterStyle, 0);
}

std::vector<css3Parser::WsContext *> css3Parser::CounterStyleContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::CounterStyleContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}

css3Parser::IdentContext* css3Parser::CounterStyleContext::ident() {
  return getRuleContext<css3Parser::IdentContext>(0);
}

css3Parser::DeclarationListContext* css3Parser::CounterStyleContext::declarationList() {
  return getRuleContext<css3Parser::DeclarationListContext>(0);
}


size_t css3Parser::CounterStyleContext::getRuleIndex() const {
  return css3Parser::RuleCounterStyle;
}

void css3Parser::CounterStyleContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCounterStyle(this);
}

void css3Parser::CounterStyleContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCounterStyle(this);
}

css3Parser::CounterStyleContext* css3Parser::counterStyle() {
  CounterStyleContext *_localctx = _tracker.createInstance<CounterStyleContext>(_ctx, getState());
  enterRule(_localctx, 140, css3Parser::RuleCounterStyle);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1017);
    match(css3Parser::CounterStyle);
    setState(1018);
    ws();
    setState(1019);
    ident();
    setState(1020);
    ws();
    setState(1021);
    match(css3Parser::T__4);
    setState(1022);
    ws();
    setState(1024);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << css3Parser::T__0)
      | (1ULL << css3Parser::T__6)
      | (1ULL << css3Parser::T__13)
      | (1ULL << css3Parser::MediaOnly)
      | (1ULL << css3Parser::Not)
      | (1ULL << css3Parser::And)
      | (1ULL << css3Parser::Or)
      | (1ULL << css3Parser::From)
      | (1ULL << css3Parser::To)
      | (1ULL << css3Parser::Variable)
      | (1ULL << css3Parser::Ident))) != 0)) {
      setState(1023);
      declarationList();
    }
    setState(1026);
    match(css3Parser::T__5);
    setState(1027);
    ws();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FontFeatureValuesRuleContext ------------------------------------------------------------------

css3Parser::FontFeatureValuesRuleContext::FontFeatureValuesRuleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* css3Parser::FontFeatureValuesRuleContext::FontFeatureValues() {
  return getToken(css3Parser::FontFeatureValues, 0);
}

std::vector<css3Parser::WsContext *> css3Parser::FontFeatureValuesRuleContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::FontFeatureValuesRuleContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}

css3Parser::FontFamilyNameListContext* css3Parser::FontFeatureValuesRuleContext::fontFamilyNameList() {
  return getRuleContext<css3Parser::FontFamilyNameListContext>(0);
}

std::vector<css3Parser::FeatureValueBlockContext *> css3Parser::FontFeatureValuesRuleContext::featureValueBlock() {
  return getRuleContexts<css3Parser::FeatureValueBlockContext>();
}

css3Parser::FeatureValueBlockContext* css3Parser::FontFeatureValuesRuleContext::featureValueBlock(size_t i) {
  return getRuleContext<css3Parser::FeatureValueBlockContext>(i);
}


size_t css3Parser::FontFeatureValuesRuleContext::getRuleIndex() const {
  return css3Parser::RuleFontFeatureValuesRule;
}

void css3Parser::FontFeatureValuesRuleContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFontFeatureValuesRule(this);
}

void css3Parser::FontFeatureValuesRuleContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFontFeatureValuesRule(this);
}

css3Parser::FontFeatureValuesRuleContext* css3Parser::fontFeatureValuesRule() {
  FontFeatureValuesRuleContext *_localctx = _tracker.createInstance<FontFeatureValuesRuleContext>(_ctx, getState());
  enterRule(_localctx, 142, css3Parser::RuleFontFeatureValuesRule);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1029);
    match(css3Parser::FontFeatureValues);
    setState(1030);
    ws();
    setState(1031);
    fontFamilyNameList();
    setState(1032);
    ws();
    setState(1033);
    match(css3Parser::T__4);
    setState(1034);
    ws();
    setState(1038);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == css3Parser::T__14) {
      setState(1035);
      featureValueBlock();
      setState(1040);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(1041);
    match(css3Parser::T__5);
    setState(1042);
    ws();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FontFamilyNameListContext ------------------------------------------------------------------

css3Parser::FontFamilyNameListContext::FontFamilyNameListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<css3Parser::FontFamilyNameContext *> css3Parser::FontFamilyNameListContext::fontFamilyName() {
  return getRuleContexts<css3Parser::FontFamilyNameContext>();
}

css3Parser::FontFamilyNameContext* css3Parser::FontFamilyNameListContext::fontFamilyName(size_t i) {
  return getRuleContext<css3Parser::FontFamilyNameContext>(i);
}

std::vector<css3Parser::WsContext *> css3Parser::FontFamilyNameListContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::FontFamilyNameListContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}

std::vector<tree::TerminalNode *> css3Parser::FontFamilyNameListContext::Comma() {
  return getTokens(css3Parser::Comma);
}

tree::TerminalNode* css3Parser::FontFamilyNameListContext::Comma(size_t i) {
  return getToken(css3Parser::Comma, i);
}


size_t css3Parser::FontFamilyNameListContext::getRuleIndex() const {
  return css3Parser::RuleFontFamilyNameList;
}

void css3Parser::FontFamilyNameListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFontFamilyNameList(this);
}

void css3Parser::FontFamilyNameListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFontFamilyNameList(this);
}

css3Parser::FontFamilyNameListContext* css3Parser::fontFamilyNameList() {
  FontFamilyNameListContext *_localctx = _tracker.createInstance<FontFamilyNameListContext>(_ctx, getState());
  enterRule(_localctx, 144, css3Parser::RuleFontFamilyNameList);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(1044);
    fontFamilyName();
    setState(1052);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 98, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(1045);
        ws();
        setState(1046);
        match(css3Parser::Comma);
        setState(1047);
        ws();
        setState(1048);
        fontFamilyName(); 
      }
      setState(1054);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 98, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FontFamilyNameContext ------------------------------------------------------------------

css3Parser::FontFamilyNameContext::FontFamilyNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* css3Parser::FontFamilyNameContext::String() {
  return getToken(css3Parser::String, 0);
}

std::vector<css3Parser::IdentContext *> css3Parser::FontFamilyNameContext::ident() {
  return getRuleContexts<css3Parser::IdentContext>();
}

css3Parser::IdentContext* css3Parser::FontFamilyNameContext::ident(size_t i) {
  return getRuleContext<css3Parser::IdentContext>(i);
}

std::vector<css3Parser::WsContext *> css3Parser::FontFamilyNameContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::FontFamilyNameContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}


size_t css3Parser::FontFamilyNameContext::getRuleIndex() const {
  return css3Parser::RuleFontFamilyName;
}

void css3Parser::FontFamilyNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFontFamilyName(this);
}

void css3Parser::FontFamilyNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFontFamilyName(this);
}

css3Parser::FontFamilyNameContext* css3Parser::fontFamilyName() {
  FontFamilyNameContext *_localctx = _tracker.createInstance<FontFamilyNameContext>(_ctx, getState());
  enterRule(_localctx, 146, css3Parser::RuleFontFamilyName);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    setState(1065);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case css3Parser::String: {
        enterOuterAlt(_localctx, 1);
        setState(1055);
        match(css3Parser::String);
        break;
      }

      case css3Parser::MediaOnly:
      case css3Parser::Not:
      case css3Parser::And:
      case css3Parser::Or:
      case css3Parser::From:
      case css3Parser::To:
      case css3Parser::Ident: {
        enterOuterAlt(_localctx, 2);
        setState(1056);
        ident();
        setState(1062);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 99, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
          if (alt == 1) {
            setState(1057);
            ws();
            setState(1058);
            ident(); 
          }
          setState(1064);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 99, _ctx);
        }
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FeatureValueBlockContext ------------------------------------------------------------------

css3Parser::FeatureValueBlockContext::FeatureValueBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

css3Parser::FeatureTypeContext* css3Parser::FeatureValueBlockContext::featureType() {
  return getRuleContext<css3Parser::FeatureTypeContext>(0);
}

std::vector<css3Parser::WsContext *> css3Parser::FeatureValueBlockContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::FeatureValueBlockContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}

std::vector<css3Parser::FeatureValueDefinitionContext *> css3Parser::FeatureValueBlockContext::featureValueDefinition() {
  return getRuleContexts<css3Parser::FeatureValueDefinitionContext>();
}

css3Parser::FeatureValueDefinitionContext* css3Parser::FeatureValueBlockContext::featureValueDefinition(size_t i) {
  return getRuleContext<css3Parser::FeatureValueDefinitionContext>(i);
}


size_t css3Parser::FeatureValueBlockContext::getRuleIndex() const {
  return css3Parser::RuleFeatureValueBlock;
}

void css3Parser::FeatureValueBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFeatureValueBlock(this);
}

void css3Parser::FeatureValueBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFeatureValueBlock(this);
}

css3Parser::FeatureValueBlockContext* css3Parser::featureValueBlock() {
  FeatureValueBlockContext *_localctx = _tracker.createInstance<FeatureValueBlockContext>(_ctx, getState());
  enterRule(_localctx, 148, css3Parser::RuleFeatureValueBlock);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1067);
    featureType();
    setState(1068);
    ws();
    setState(1069);
    match(css3Parser::T__4);
    setState(1070);
    ws();
    setState(1072);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << css3Parser::MediaOnly)
      | (1ULL << css3Parser::Not)
      | (1ULL << css3Parser::And)
      | (1ULL << css3Parser::Or)
      | (1ULL << css3Parser::From)
      | (1ULL << css3Parser::To)
      | (1ULL << css3Parser::Ident))) != 0)) {
      setState(1071);
      featureValueDefinition();
    }
    setState(1082);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << css3Parser::T__0)
      | (1ULL << css3Parser::Comment)
      | (1ULL << css3Parser::Space))) != 0)) {
      setState(1074);
      ws();
      setState(1075);
      match(css3Parser::T__0);
      setState(1076);
      ws();
      setState(1078);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << css3Parser::MediaOnly)
        | (1ULL << css3Parser::Not)
        | (1ULL << css3Parser::And)
        | (1ULL << css3Parser::Or)
        | (1ULL << css3Parser::From)
        | (1ULL << css3Parser::To)
        | (1ULL << css3Parser::Ident))) != 0)) {
        setState(1077);
        featureValueDefinition();
      }
      setState(1084);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(1085);
    match(css3Parser::T__5);
    setState(1086);
    ws();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FeatureTypeContext ------------------------------------------------------------------

css3Parser::FeatureTypeContext::FeatureTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

css3Parser::AtKeywordContext* css3Parser::FeatureTypeContext::atKeyword() {
  return getRuleContext<css3Parser::AtKeywordContext>(0);
}


size_t css3Parser::FeatureTypeContext::getRuleIndex() const {
  return css3Parser::RuleFeatureType;
}

void css3Parser::FeatureTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFeatureType(this);
}

void css3Parser::FeatureTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFeatureType(this);
}

css3Parser::FeatureTypeContext* css3Parser::featureType() {
  FeatureTypeContext *_localctx = _tracker.createInstance<FeatureTypeContext>(_ctx, getState());
  enterRule(_localctx, 150, css3Parser::RuleFeatureType);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1088);
    atKeyword();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FeatureValueDefinitionContext ------------------------------------------------------------------

css3Parser::FeatureValueDefinitionContext::FeatureValueDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

css3Parser::IdentContext* css3Parser::FeatureValueDefinitionContext::ident() {
  return getRuleContext<css3Parser::IdentContext>(0);
}

std::vector<css3Parser::WsContext *> css3Parser::FeatureValueDefinitionContext::ws() {
  return getRuleContexts<css3Parser::WsContext>();
}

css3Parser::WsContext* css3Parser::FeatureValueDefinitionContext::ws(size_t i) {
  return getRuleContext<css3Parser::WsContext>(i);
}

std::vector<css3Parser::NumberContext *> css3Parser::FeatureValueDefinitionContext::number() {
  return getRuleContexts<css3Parser::NumberContext>();
}

css3Parser::NumberContext* css3Parser::FeatureValueDefinitionContext::number(size_t i) {
  return getRuleContext<css3Parser::NumberContext>(i);
}


size_t css3Parser::FeatureValueDefinitionContext::getRuleIndex() const {
  return css3Parser::RuleFeatureValueDefinition;
}

void css3Parser::FeatureValueDefinitionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFeatureValueDefinition(this);
}

void css3Parser::FeatureValueDefinitionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFeatureValueDefinition(this);
}

css3Parser::FeatureValueDefinitionContext* css3Parser::featureValueDefinition() {
  FeatureValueDefinitionContext *_localctx = _tracker.createInstance<FeatureValueDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 152, css3Parser::RuleFeatureValueDefinition);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(1090);
    ident();
    setState(1091);
    ws();
    setState(1092);
    match(css3Parser::T__2);
    setState(1093);
    ws();
    setState(1094);
    number();
    setState(1100);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 104, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(1095);
        ws();
        setState(1096);
        number(); 
      }
      setState(1102);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 104, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdentContext ------------------------------------------------------------------

css3Parser::IdentContext::IdentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* css3Parser::IdentContext::Ident() {
  return getToken(css3Parser::Ident, 0);
}

tree::TerminalNode* css3Parser::IdentContext::MediaOnly() {
  return getToken(css3Parser::MediaOnly, 0);
}

tree::TerminalNode* css3Parser::IdentContext::Not() {
  return getToken(css3Parser::Not, 0);
}

tree::TerminalNode* css3Parser::IdentContext::And() {
  return getToken(css3Parser::And, 0);
}

tree::TerminalNode* css3Parser::IdentContext::Or() {
  return getToken(css3Parser::Or, 0);
}

tree::TerminalNode* css3Parser::IdentContext::From() {
  return getToken(css3Parser::From, 0);
}

tree::TerminalNode* css3Parser::IdentContext::To() {
  return getToken(css3Parser::To, 0);
}


size_t css3Parser::IdentContext::getRuleIndex() const {
  return css3Parser::RuleIdent;
}

void css3Parser::IdentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIdent(this);
}

void css3Parser::IdentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIdent(this);
}

css3Parser::IdentContext* css3Parser::ident() {
  IdentContext *_localctx = _tracker.createInstance<IdentContext>(_ctx, getState());
  enterRule(_localctx, 154, css3Parser::RuleIdent);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1103);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << css3Parser::MediaOnly)
      | (1ULL << css3Parser::Not)
      | (1ULL << css3Parser::And)
      | (1ULL << css3Parser::Or)
      | (1ULL << css3Parser::From)
      | (1ULL << css3Parser::To)
      | (1ULL << css3Parser::Ident))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- WsContext ------------------------------------------------------------------

css3Parser::WsContext::WsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> css3Parser::WsContext::Comment() {
  return getTokens(css3Parser::Comment);
}

tree::TerminalNode* css3Parser::WsContext::Comment(size_t i) {
  return getToken(css3Parser::Comment, i);
}

std::vector<tree::TerminalNode *> css3Parser::WsContext::Space() {
  return getTokens(css3Parser::Space);
}

tree::TerminalNode* css3Parser::WsContext::Space(size_t i) {
  return getToken(css3Parser::Space, i);
}


size_t css3Parser::WsContext::getRuleIndex() const {
  return css3Parser::RuleWs;
}

void css3Parser::WsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWs(this);
}

void css3Parser::WsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<css3Listener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWs(this);
}

css3Parser::WsContext* css3Parser::ws() {
  WsContext *_localctx = _tracker.createInstance<WsContext>(_ctx, getState());
  enterRule(_localctx, 156, css3Parser::RuleWs);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(1108);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 105, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(1105);
        _la = _input->LA(1);
        if (!(_la == css3Parser::Comment

        || _la == css3Parser::Space)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        } 
      }
      setState(1110);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 105, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

// Static vars and initialization.
std::vector<dfa::DFA> css3Parser::_decisionToDFA;
atn::PredictionContextCache css3Parser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN css3Parser::_atn;
std::vector<uint16_t> css3Parser::_serializedATN;

std::vector<std::string> css3Parser::_ruleNames = {
  "stylesheet", "charset", "imports", "cssnamespace", "namespacePrefix", 
  "media", "mediaQueryList", "mediaQuery", "mediaType", "mediaExpression", 
  "mediaFeature", "page", "pseudoPage", "selectorGroup", "selector", "combinator", 
  "simpleSelectorSequence", "typeSelector", "typeNamespacePrefix", "elementName", 
  "universal", "className", "attrib", "pseudo", "functionalPseudo", "expression", 
  "negation", "negationArg", "cssoperator", "property", "ruleset", "declarationList", 
  "declaration", "prio", "value", "expr", "term", "function", "dxImageTransform", 
  "hexcolor", "number", "percentage", "dimension", "unknownDimension", "any", 
  "atRule", "atKeyword", "unused", "block", "nestedStatement", "groupRuleBody", 
  "supportsRule", "supportsCondition", "supportsConditionInParens", "supportsNegation", 
  "supportsConjunction", "supportsDisjunction", "supportsDeclarationCondition", 
  "generalEnclosed", "var", "calc", "calcSum", "calcProduct", "calcValue", 
  "fontFaceRule", "fontFaceDeclaration", "keyframesRule", "keyframesBlocks", 
  "keyframeSelector", "viewport", "counterStyle", "fontFeatureValuesRule", 
  "fontFamilyNameList", "fontFamilyName", "featureValueBlock", "featureType", 
  "featureValueDefinition", "ident", "ws"
};

std::vector<std::string> css3Parser::_literalNames = {
  "", "';'", "'('", "':'", "')'", "'{'", "'}'", "'*'", "'|'", "'.'", "'['", 
  "'='", "']'", "'/'", "'_'", "'@'", "", "", "'<!--'", "'-->'", "'~='", 
  "'|='", "", "", "", "", "", "'@charset '", "", "", "", "", "", "", "", 
  "", "", "'+'", "'-'", "'>'", "','", "'~'", "", "", "", "'^='", "'$='", 
  "'*='", "", "", "", "", "", "", "'calc('", "", "", "", "", "", "'var('"
};

std::vector<std::string> css3Parser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "Comment", 
  "Space", "Cdo", "Cdc", "Includes", "DashMatch", "Hash", "Import", "Page", 
  "Media", "Namespace", "Charset", "Important", "Percentage", "Uri", "UnicodeRange", 
  "MediaOnly", "Not", "And", "Dimension", "UnknownDimension", "Plus", "Minus", 
  "Greater", "Comma", "Tilde", "PseudoNot", "Number", "String", "PrefixMatch", 
  "SuffixMatch", "SubstringMatch", "FontFace", "Supports", "Or", "Keyframes", 
  "From", "To", "Calc", "Viewport", "CounterStyle", "FontFeatureValues", 
  "DxImageTransform", "Variable", "Var", "Ident", "Function"
};

dfa::Vocabulary css3Parser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> css3Parser::_tokenNames;

css3Parser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x40, 0x45a, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
    0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 
    0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 
    0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 
    0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 
    0x12, 0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 0x9, 0x14, 0x4, 0x15, 
    0x9, 0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 0x9, 0x17, 0x4, 0x18, 0x9, 
    0x18, 0x4, 0x19, 0x9, 0x19, 0x4, 0x1a, 0x9, 0x1a, 0x4, 0x1b, 0x9, 0x1b, 
    0x4, 0x1c, 0x9, 0x1c, 0x4, 0x1d, 0x9, 0x1d, 0x4, 0x1e, 0x9, 0x1e, 0x4, 
    0x1f, 0x9, 0x1f, 0x4, 0x20, 0x9, 0x20, 0x4, 0x21, 0x9, 0x21, 0x4, 0x22, 
    0x9, 0x22, 0x4, 0x23, 0x9, 0x23, 0x4, 0x24, 0x9, 0x24, 0x4, 0x25, 0x9, 
    0x25, 0x4, 0x26, 0x9, 0x26, 0x4, 0x27, 0x9, 0x27, 0x4, 0x28, 0x9, 0x28, 
    0x4, 0x29, 0x9, 0x29, 0x4, 0x2a, 0x9, 0x2a, 0x4, 0x2b, 0x9, 0x2b, 0x4, 
    0x2c, 0x9, 0x2c, 0x4, 0x2d, 0x9, 0x2d, 0x4, 0x2e, 0x9, 0x2e, 0x4, 0x2f, 
    0x9, 0x2f, 0x4, 0x30, 0x9, 0x30, 0x4, 0x31, 0x9, 0x31, 0x4, 0x32, 0x9, 
    0x32, 0x4, 0x33, 0x9, 0x33, 0x4, 0x34, 0x9, 0x34, 0x4, 0x35, 0x9, 0x35, 
    0x4, 0x36, 0x9, 0x36, 0x4, 0x37, 0x9, 0x37, 0x4, 0x38, 0x9, 0x38, 0x4, 
    0x39, 0x9, 0x39, 0x4, 0x3a, 0x9, 0x3a, 0x4, 0x3b, 0x9, 0x3b, 0x4, 0x3c, 
    0x9, 0x3c, 0x4, 0x3d, 0x9, 0x3d, 0x4, 0x3e, 0x9, 0x3e, 0x4, 0x3f, 0x9, 
    0x3f, 0x4, 0x40, 0x9, 0x40, 0x4, 0x41, 0x9, 0x41, 0x4, 0x42, 0x9, 0x42, 
    0x4, 0x43, 0x9, 0x43, 0x4, 0x44, 0x9, 0x44, 0x4, 0x45, 0x9, 0x45, 0x4, 
    0x46, 0x9, 0x46, 0x4, 0x47, 0x9, 0x47, 0x4, 0x48, 0x9, 0x48, 0x4, 0x49, 
    0x9, 0x49, 0x4, 0x4a, 0x9, 0x4a, 0x4, 0x4b, 0x9, 0x4b, 0x4, 0x4c, 0x9, 
    0x4c, 0x4, 0x4d, 0x9, 0x4d, 0x4, 0x4e, 0x9, 0x4e, 0x4, 0x4f, 0x9, 0x4f, 
    0x4, 0x50, 0x9, 0x50, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x7, 0x2, 0xa4, 
    0xa, 0x2, 0xc, 0x2, 0xe, 0x2, 0xa7, 0xb, 0x2, 0x7, 0x2, 0xa9, 0xa, 0x2, 
    0xc, 0x2, 0xe, 0x2, 0xac, 0xb, 0x2, 0x3, 0x2, 0x3, 0x2, 0x7, 0x2, 0xb0, 
    0xa, 0x2, 0xc, 0x2, 0xe, 0x2, 0xb3, 0xb, 0x2, 0x7, 0x2, 0xb5, 0xa, 0x2, 
    0xc, 0x2, 0xe, 0x2, 0xb8, 0xb, 0x2, 0x3, 0x2, 0x3, 0x2, 0x7, 0x2, 0xbc, 
    0xa, 0x2, 0xc, 0x2, 0xe, 0x2, 0xbf, 0xb, 0x2, 0x7, 0x2, 0xc1, 0xa, 0x2, 
    0xc, 0x2, 0xe, 0x2, 0xc4, 0xb, 0x2, 0x3, 0x2, 0x3, 0x2, 0x7, 0x2, 0xc8, 
    0xa, 0x2, 0xc, 0x2, 0xe, 0x2, 0xcb, 0xb, 0x2, 0x7, 0x2, 0xcd, 0xa, 0x2, 
    0xc, 0x2, 0xe, 0x2, 0xd0, 0xb, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x5, 0x3, 0xde, 0xa, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 
    0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 
    0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 
    0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 
    0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 0xfa, 0xa, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 
    0x5, 0x3, 0x5, 0x3, 0x5, 0x5, 0x5, 0x101, 0xa, 0x5, 0x3, 0x5, 0x3, 0x5, 
    0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 
    0x3, 0x5, 0x5, 0x5, 0x10d, 0xa, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x5, 
    0x5, 0x112, 0xa, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 
    0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 
    0x3, 0x8, 0x7, 0x8, 0x121, 0xa, 0x8, 0xc, 0x8, 0xe, 0x8, 0x124, 0xb, 
    0x8, 0x5, 0x8, 0x126, 0xa, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x9, 0x5, 0x9, 
    0x12b, 0xa, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 
    0x9, 0x3, 0x9, 0x7, 0x9, 0x134, 0xa, 0x9, 0xc, 0x9, 0xe, 0x9, 0x137, 
    0xb, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x7, 0x9, 
    0x13e, 0xa, 0x9, 0xc, 0x9, 0xe, 0x9, 0x141, 0xb, 0x9, 0x5, 0x9, 0x143, 
    0xa, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 
    0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x5, 0xb, 0x14e, 0xa, 0xb, 0x3, 0xb, 0x3, 
    0xb, 0x3, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 
    0xd, 0x5, 0xd, 0x159, 0xa, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x5, 0xd, 
    0x15e, 0xa, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x5, 0xd, 0x163, 0xa, 
    0xd, 0x7, 0xd, 0x165, 0xa, 0xd, 0xc, 0xd, 0xe, 0xd, 0x168, 0xb, 0xd, 
    0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 
    0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x7, 0xf, 0x176, 0xa, 
    0xf, 0xc, 0xf, 0xe, 0xf, 0x179, 0xb, 0xf, 0x3, 0x10, 0x3, 0x10, 0x3, 
    0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x7, 0x10, 0x181, 0xa, 0x10, 
    0xc, 0x10, 0xe, 0x10, 0x184, 0xb, 0x10, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 
    0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x5, 0x11, 0x18e, 
    0xa, 0x11, 0x3, 0x12, 0x3, 0x12, 0x5, 0x12, 0x192, 0xa, 0x12, 0x3, 0x12, 
    0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x7, 0x12, 0x199, 0xa, 0x12, 
    0xc, 0x12, 0xe, 0x12, 0x19c, 0xb, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 
    0x3, 0x12, 0x3, 0x12, 0x6, 0x12, 0x1a3, 0xa, 0x12, 0xd, 0x12, 0xe, 0x12, 
    0x1a4, 0x5, 0x12, 0x1a7, 0xa, 0x12, 0x3, 0x13, 0x5, 0x13, 0x1aa, 0xa, 
    0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x14, 0x3, 0x14, 0x5, 0x14, 0x1b0, 
    0xa, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x15, 0x3, 0x15, 0x3, 0x16, 0x5, 
    0x16, 0x1b7, 0xa, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x17, 0x3, 0x17, 
    0x3, 0x17, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x5, 0x18, 0x1c1, 0xa, 0x18, 
    0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x5, 
    0x18, 0x1c9, 0xa, 0x18, 0x3, 0x18, 0x3, 0x18, 0x5, 0x18, 0x1cd, 0xa, 
    0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x19, 0x3, 0x19, 0x5, 0x19, 0x1d3, 
    0xa, 0x19, 0x3, 0x19, 0x3, 0x19, 0x5, 0x19, 0x1d7, 0xa, 0x19, 0x3, 0x1a, 
    0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1b, 0x3, 0x1b, 0x3, 
    0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x5, 0x1b, 0x1e5, 
    0xa, 0x1b, 0x3, 0x1b, 0x6, 0x1b, 0x1e8, 0xa, 0x1b, 0xd, 0x1b, 0xe, 0x1b, 
    0x1e9, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 
    0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x5, 
    0x1d, 0x1f8, 0xa, 0x1d, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 
    0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x5, 0x1e, 0x202, 0xa, 0x1e, 
    0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 
    0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x5, 0x1f, 0x20d, 0xa, 0x1f, 0x3, 0x20, 
    0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x5, 0x20, 0x213, 0xa, 0x20, 0x3, 0x20, 
    0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x7, 0x20, 0x219, 0xa, 0x20, 0xc, 0x20, 
    0xe, 0x20, 0x21c, 0xb, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x5, 0x20, 
    0x221, 0xa, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x5, 0x20, 0x226, 
    0xa, 0x20, 0x3, 0x21, 0x3, 0x21, 0x7, 0x21, 0x22a, 0xa, 0x21, 0xc, 0x21, 
    0xe, 0x21, 0x22d, 0xb, 0x21, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 
    0x3, 0x21, 0x5, 0x21, 0x234, 0xa, 0x21, 0x7, 0x21, 0x236, 0xa, 0x21, 
    0xc, 0x21, 0xe, 0x21, 0x239, 0xb, 0x21, 0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 
    0x3, 0x22, 0x3, 0x22, 0x5, 0x22, 0x240, 0xa, 0x22, 0x3, 0x22, 0x3, 0x22, 
    0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x5, 0x22, 0x247, 0xa, 0x22, 0x3, 0x23, 
    0x3, 0x23, 0x3, 0x23, 0x3, 0x24, 0x3, 0x24, 0x3, 0x24, 0x3, 0x24, 0x3, 
    0x24, 0x6, 0x24, 0x251, 0xa, 0x24, 0xd, 0x24, 0xe, 0x24, 0x252, 0x3, 
    0x25, 0x3, 0x25, 0x5, 0x25, 0x257, 0xa, 0x25, 0x3, 0x25, 0x7, 0x25, 
    0x25a, 0xa, 0x25, 0xc, 0x25, 0xe, 0x25, 0x25d, 0xb, 0x25, 0x3, 0x26, 
    0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 
    0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 
    0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 
    0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x5, 0x26, 
    0x279, 0xa, 0x26, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 
    0x3, 0x27, 0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 0x3, 
    0x28, 0x3, 0x29, 0x3, 0x29, 0x3, 0x29, 0x3, 0x2a, 0x5, 0x2a, 0x28b, 
    0xa, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2b, 0x5, 0x2b, 0x290, 0xa, 0x2b, 
    0x3, 0x2b, 0x3, 0x2b, 0x3, 0x2c, 0x5, 0x2c, 0x295, 0xa, 0x2c, 0x3, 0x2c, 
    0x3, 0x2c, 0x3, 0x2d, 0x5, 0x2d, 0x29a, 0xa, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 
    0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 
    0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 
    0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 
    0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 
    0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 
    0x2e, 0x7, 0x2e, 0x2bf, 0xa, 0x2e, 0xc, 0x2e, 0xe, 0x2e, 0x2c2, 0xb, 
    0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 
    0x3, 0x2e, 0x7, 0x2e, 0x2cb, 0xa, 0x2e, 0xc, 0x2e, 0xe, 0x2e, 0x2ce, 
    0xb, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 
    0x2e, 0x3, 0x2e, 0x7, 0x2e, 0x2d7, 0xa, 0x2e, 0xc, 0x2e, 0xe, 0x2e, 
    0x2da, 0xb, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x5, 0x2e, 0x2df, 
    0xa, 0x2e, 0x3, 0x2f, 0x3, 0x2f, 0x3, 0x2f, 0x7, 0x2f, 0x2e4, 0xa, 0x2f, 
    0xc, 0x2f, 0xe, 0x2f, 0x2e7, 0xb, 0x2f, 0x3, 0x2f, 0x3, 0x2f, 0x3, 0x2f, 
    0x5, 0x2f, 0x2ec, 0xa, 0x2f, 0x3, 0x30, 0x3, 0x30, 0x3, 0x30, 0x3, 0x31, 
    0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 
    0x31, 0x3, 0x31, 0x3, 0x31, 0x5, 0x31, 0x2fb, 0xa, 0x31, 0x3, 0x32, 
    0x3, 0x32, 0x3, 0x32, 0x3, 0x32, 0x3, 0x32, 0x3, 0x32, 0x3, 0x32, 0x3, 
    0x32, 0x3, 0x32, 0x3, 0x32, 0x3, 0x32, 0x7, 0x32, 0x308, 0xa, 0x32, 
    0xc, 0x32, 0xe, 0x32, 0x30b, 0xb, 0x32, 0x3, 0x32, 0x3, 0x32, 0x3, 0x32, 
    0x3, 0x33, 0x3, 0x33, 0x3, 0x33, 0x3, 0x33, 0x3, 0x33, 0x3, 0x33, 0x3, 
    0x33, 0x3, 0x33, 0x3, 0x33, 0x3, 0x33, 0x5, 0x33, 0x31a, 0xa, 0x33, 
    0x3, 0x34, 0x3, 0x34, 0x3, 0x34, 0x7, 0x34, 0x31f, 0xa, 0x34, 0xc, 0x34, 
    0xe, 0x34, 0x322, 0xb, 0x34, 0x3, 0x34, 0x3, 0x34, 0x3, 0x34, 0x3, 0x35, 
    0x3, 0x35, 0x3, 0x35, 0x3, 0x35, 0x3, 0x35, 0x3, 0x35, 0x3, 0x36, 0x3, 
    0x36, 0x3, 0x36, 0x3, 0x36, 0x5, 0x36, 0x331, 0xa, 0x36, 0x3, 0x37, 
    0x3, 0x37, 0x3, 0x37, 0x3, 0x37, 0x3, 0x37, 0x3, 0x37, 0x3, 0x37, 0x3, 
    0x37, 0x5, 0x37, 0x33b, 0xa, 0x37, 0x3, 0x38, 0x3, 0x38, 0x3, 0x38, 
    0x3, 0x38, 0x3, 0x38, 0x3, 0x38, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 
    0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 
    0x6, 0x39, 0x34d, 0xa, 0x39, 0xd, 0x39, 0xe, 0x39, 0x34e, 0x3, 0x3a, 
    0x3, 0x3a, 0x3, 0x3a, 0x3, 0x3a, 0x3, 0x3a, 0x3, 0x3a, 0x3, 0x3a, 0x3, 
    0x3a, 0x3, 0x3a, 0x3, 0x3a, 0x6, 0x3a, 0x35b, 0xa, 0x3a, 0xd, 0x3a, 
    0xe, 0x3a, 0x35c, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 
    0x3, 0x3c, 0x3, 0x3c, 0x3, 0x3c, 0x7, 0x3c, 0x367, 0xa, 0x3c, 0xc, 0x3c, 
    0xe, 0x3c, 0x36a, 0xb, 0x3c, 0x3, 0x3c, 0x3, 0x3c, 0x3, 0x3d, 0x3, 0x3d, 
    0x3, 0x3d, 0x3, 0x3d, 0x3, 0x3d, 0x3, 0x3d, 0x3, 0x3d, 0x3, 0x3e, 0x3, 
    0x3e, 0x3, 0x3e, 0x3, 0x3e, 0x3, 0x3e, 0x3, 0x3e, 0x3, 0x3f, 0x3, 0x3f, 
    0x3, 0x3f, 0x3, 0x3f, 0x3, 0x3f, 0x3, 0x3f, 0x3, 0x3f, 0x3, 0x3f, 0x3, 
    0x3f, 0x7, 0x3f, 0x384, 0xa, 0x3f, 0xc, 0x3f, 0xe, 0x3f, 0x387, 0xb, 
    0x3f, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 
    0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 0x7, 0x40, 0x393, 0xa, 0x40, 
    0xc, 0x40, 0xe, 0x40, 0x396, 0xb, 0x40, 0x3, 0x41, 0x3, 0x41, 0x3, 0x41, 
    0x3, 0x41, 0x3, 0x41, 0x3, 0x41, 0x3, 0x41, 0x3, 0x41, 0x3, 0x41, 0x3, 
    0x41, 0x3, 0x41, 0x3, 0x41, 0x3, 0x41, 0x3, 0x41, 0x3, 0x41, 0x3, 0x41, 
    0x3, 0x41, 0x3, 0x41, 0x5, 0x41, 0x3aa, 0xa, 0x41, 0x3, 0x42, 0x3, 0x42, 
    0x3, 0x42, 0x3, 0x42, 0x3, 0x42, 0x5, 0x42, 0x3b1, 0xa, 0x42, 0x3, 0x42, 
    0x3, 0x42, 0x3, 0x42, 0x5, 0x42, 0x3b6, 0xa, 0x42, 0x7, 0x42, 0x3b8, 
    0xa, 0x42, 0xc, 0x42, 0xe, 0x42, 0x3bb, 0xb, 0x42, 0x3, 0x42, 0x3, 0x42, 
    0x3, 0x42, 0x3, 0x43, 0x3, 0x43, 0x3, 0x43, 0x3, 0x43, 0x3, 0x43, 0x3, 
    0x43, 0x3, 0x43, 0x3, 0x43, 0x3, 0x43, 0x3, 0x43, 0x5, 0x43, 0x3ca, 
    0xa, 0x43, 0x3, 0x44, 0x3, 0x44, 0x3, 0x44, 0x3, 0x44, 0x3, 0x44, 0x3, 
    0x44, 0x3, 0x44, 0x3, 0x44, 0x3, 0x44, 0x3, 0x44, 0x3, 0x44, 0x3, 0x44, 
    0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 0x5, 0x45, 0x3dc, 0xa, 0x45, 
    0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 0x7, 0x45, 0x3e1, 0xa, 0x45, 0xc, 0x45, 
    0xe, 0x45, 0x3e4, 0xb, 0x45, 0x3, 0x46, 0x3, 0x46, 0x3, 0x46, 0x3, 0x46, 
    0x3, 0x46, 0x3, 0x46, 0x3, 0x46, 0x7, 0x46, 0x3ed, 0xa, 0x46, 0xc, 0x46, 
    0xe, 0x46, 0x3f0, 0xb, 0x46, 0x3, 0x47, 0x3, 0x47, 0x3, 0x47, 0x3, 0x47, 
    0x3, 0x47, 0x5, 0x47, 0x3f7, 0xa, 0x47, 0x3, 0x47, 0x3, 0x47, 0x3, 0x47, 
    0x3, 0x48, 0x3, 0x48, 0x3, 0x48, 0x3, 0x48, 0x3, 0x48, 0x3, 0x48, 0x3, 
    0x48, 0x5, 0x48, 0x403, 0xa, 0x48, 0x3, 0x48, 0x3, 0x48, 0x3, 0x48, 
    0x3, 0x49, 0x3, 0x49, 0x3, 0x49, 0x3, 0x49, 0x3, 0x49, 0x3, 0x49, 0x3, 
    0x49, 0x7, 0x49, 0x40f, 0xa, 0x49, 0xc, 0x49, 0xe, 0x49, 0x412, 0xb, 
    0x49, 0x3, 0x49, 0x3, 0x49, 0x3, 0x49, 0x3, 0x4a, 0x3, 0x4a, 0x3, 0x4a, 
    0x3, 0x4a, 0x3, 0x4a, 0x3, 0x4a, 0x7, 0x4a, 0x41d, 0xa, 0x4a, 0xc, 0x4a, 
    0xe, 0x4a, 0x420, 0xb, 0x4a, 0x3, 0x4b, 0x3, 0x4b, 0x3, 0x4b, 0x3, 0x4b, 
    0x3, 0x4b, 0x7, 0x4b, 0x427, 0xa, 0x4b, 0xc, 0x4b, 0xe, 0x4b, 0x42a, 
    0xb, 0x4b, 0x5, 0x4b, 0x42c, 0xa, 0x4b, 0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 
    0x3, 0x4c, 0x3, 0x4c, 0x5, 0x4c, 0x433, 0xa, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 
    0x3, 0x4c, 0x3, 0x4c, 0x5, 0x4c, 0x439, 0xa, 0x4c, 0x7, 0x4c, 0x43b, 
    0xa, 0x4c, 0xc, 0x4c, 0xe, 0x4c, 0x43e, 0xb, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 
    0x3, 0x4c, 0x3, 0x4d, 0x3, 0x4d, 0x3, 0x4e, 0x3, 0x4e, 0x3, 0x4e, 0x3, 
    0x4e, 0x3, 0x4e, 0x3, 0x4e, 0x3, 0x4e, 0x3, 0x4e, 0x7, 0x4e, 0x44d, 
    0xa, 0x4e, 0xc, 0x4e, 0xe, 0x4e, 0x450, 0xb, 0x4e, 0x3, 0x4f, 0x3, 0x4f, 
    0x3, 0x50, 0x7, 0x50, 0x455, 0xa, 0x50, 0xc, 0x50, 0xe, 0x50, 0x458, 
    0xb, 0x50, 0x3, 0x50, 0x2, 0x2, 0x51, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 
    0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x24, 
    0x26, 0x28, 0x2a, 0x2c, 0x2e, 0x30, 0x32, 0x34, 0x36, 0x38, 0x3a, 0x3c, 
    0x3e, 0x40, 0x42, 0x44, 0x46, 0x48, 0x4a, 0x4c, 0x4e, 0x50, 0x52, 0x54, 
    0x56, 0x58, 0x5a, 0x5c, 0x5e, 0x60, 0x62, 0x64, 0x66, 0x68, 0x6a, 0x6c, 
    0x6e, 0x70, 0x72, 0x74, 0x76, 0x78, 0x7a, 0x7c, 0x7e, 0x80, 0x82, 0x84, 
    0x86, 0x88, 0x8a, 0x8c, 0x8e, 0x90, 0x92, 0x94, 0x96, 0x98, 0x9a, 0x9c, 
    0x9e, 0x2, 0xb, 0x3, 0x2, 0x12, 0x15, 0x4, 0x2, 0x20, 0x20, 0x2e, 0x2e, 
    0x3, 0x2, 0x22, 0x23, 0x5, 0x2, 0xd, 0xd, 0x16, 0x17, 0x2f, 0x31, 0x3, 
    0x2, 0x27, 0x28, 0x4, 0x2, 0x4, 0x4, 0x40, 0x40, 0x4, 0x2, 0x1f, 0x1f, 
    0x36, 0x37, 0x6, 0x2, 0x22, 0x24, 0x34, 0x34, 0x36, 0x37, 0x3f, 0x3f, 
    0x3, 0x2, 0x12, 0x13, 0x2, 0x4ba, 0x2, 0xa0, 0x3, 0x2, 0x2, 0x2, 0x4, 
    0xdd, 0x3, 0x2, 0x2, 0x2, 0x6, 0xf9, 0x3, 0x2, 0x2, 0x2, 0x8, 0x111, 
    0x3, 0x2, 0x2, 0x2, 0xa, 0x113, 0x3, 0x2, 0x2, 0x2, 0xc, 0x115, 0x3, 
    0x2, 0x2, 0x2, 0xe, 0x125, 0x3, 0x2, 0x2, 0x2, 0x10, 0x142, 0x3, 0x2, 
    0x2, 0x2, 0x12, 0x144, 0x3, 0x2, 0x2, 0x2, 0x14, 0x146, 0x3, 0x2, 0x2, 
    0x2, 0x16, 0x152, 0x3, 0x2, 0x2, 0x2, 0x18, 0x155, 0x3, 0x2, 0x2, 0x2, 
    0x1a, 0x16c, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x170, 0x3, 0x2, 0x2, 0x2, 0x1e, 
    0x17a, 0x3, 0x2, 0x2, 0x2, 0x20, 0x18d, 0x3, 0x2, 0x2, 0x2, 0x22, 0x1a6, 
    0x3, 0x2, 0x2, 0x2, 0x24, 0x1a9, 0x3, 0x2, 0x2, 0x2, 0x26, 0x1af, 0x3, 
    0x2, 0x2, 0x2, 0x28, 0x1b3, 0x3, 0x2, 0x2, 0x2, 0x2a, 0x1b6, 0x3, 0x2, 
    0x2, 0x2, 0x2c, 0x1ba, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x1bd, 0x3, 0x2, 0x2, 
    0x2, 0x30, 0x1d0, 0x3, 0x2, 0x2, 0x2, 0x32, 0x1d8, 0x3, 0x2, 0x2, 0x2, 
    0x34, 0x1e7, 0x3, 0x2, 0x2, 0x2, 0x36, 0x1eb, 0x3, 0x2, 0x2, 0x2, 0x38, 
    0x1f7, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x201, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x20c, 
    0x3, 0x2, 0x2, 0x2, 0x3e, 0x225, 0x3, 0x2, 0x2, 0x2, 0x40, 0x22b, 0x3, 
    0x2, 0x2, 0x2, 0x42, 0x246, 0x3, 0x2, 0x2, 0x2, 0x44, 0x248, 0x3, 0x2, 
    0x2, 0x2, 0x46, 0x250, 0x3, 0x2, 0x2, 0x2, 0x48, 0x254, 0x3, 0x2, 0x2, 
    0x2, 0x4a, 0x278, 0x3, 0x2, 0x2, 0x2, 0x4c, 0x27a, 0x3, 0x2, 0x2, 0x2, 
    0x4e, 0x280, 0x3, 0x2, 0x2, 0x2, 0x50, 0x286, 0x3, 0x2, 0x2, 0x2, 0x52, 
    0x28a, 0x3, 0x2, 0x2, 0x2, 0x54, 0x28f, 0x3, 0x2, 0x2, 0x2, 0x56, 0x294, 
    0x3, 0x2, 0x2, 0x2, 0x58, 0x299, 0x3, 0x2, 0x2, 0x2, 0x5a, 0x2de, 0x3, 
    0x2, 0x2, 0x2, 0x5c, 0x2e0, 0x3, 0x2, 0x2, 0x2, 0x5e, 0x2ed, 0x3, 0x2, 
    0x2, 0x2, 0x60, 0x2fa, 0x3, 0x2, 0x2, 0x2, 0x62, 0x2fc, 0x3, 0x2, 0x2, 
    0x2, 0x64, 0x319, 0x3, 0x2, 0x2, 0x2, 0x66, 0x31b, 0x3, 0x2, 0x2, 0x2, 
    0x68, 0x326, 0x3, 0x2, 0x2, 0x2, 0x6a, 0x330, 0x3, 0x2, 0x2, 0x2, 0x6c, 
    0x33a, 0x3, 0x2, 0x2, 0x2, 0x6e, 0x33c, 0x3, 0x2, 0x2, 0x2, 0x70, 0x342, 
    0x3, 0x2, 0x2, 0x2, 0x72, 0x350, 0x3, 0x2, 0x2, 0x2, 0x74, 0x35e, 0x3, 
    0x2, 0x2, 0x2, 0x76, 0x363, 0x3, 0x2, 0x2, 0x2, 0x78, 0x36d, 0x3, 0x2, 
    0x2, 0x2, 0x7a, 0x374, 0x3, 0x2, 0x2, 0x2, 0x7c, 0x37a, 0x3, 0x2, 0x2, 
    0x2, 0x7e, 0x388, 0x3, 0x2, 0x2, 0x2, 0x80, 0x3a9, 0x3, 0x2, 0x2, 0x2, 
    0x82, 0x3ab, 0x3, 0x2, 0x2, 0x2, 0x84, 0x3c9, 0x3, 0x2, 0x2, 0x2, 0x86, 
    0x3cb, 0x3, 0x2, 0x2, 0x2, 0x88, 0x3e2, 0x3, 0x2, 0x2, 0x2, 0x8a, 0x3e5, 
    0x3, 0x2, 0x2, 0x2, 0x8c, 0x3f1, 0x3, 0x2, 0x2, 0x2, 0x8e, 0x3fb, 0x3, 
    0x2, 0x2, 0x2, 0x90, 0x407, 0x3, 0x2, 0x2, 0x2, 0x92, 0x416, 0x3, 0x2, 
    0x2, 0x2, 0x94, 0x42b, 0x3, 0x2, 0x2, 0x2, 0x96, 0x42d, 0x3, 0x2, 0x2, 
    0x2, 0x98, 0x442, 0x3, 0x2, 0x2, 0x2, 0x9a, 0x444, 0x3, 0x2, 0x2, 0x2, 
    0x9c, 0x451, 0x3, 0x2, 0x2, 0x2, 0x9e, 0x456, 0x3, 0x2, 0x2, 0x2, 0xa0, 
    0xaa, 0x5, 0x9e, 0x50, 0x2, 0xa1, 0xa5, 0x5, 0x4, 0x3, 0x2, 0xa2, 0xa4, 
    0x9, 0x2, 0x2, 0x2, 0xa3, 0xa2, 0x3, 0x2, 0x2, 0x2, 0xa4, 0xa7, 0x3, 
    0x2, 0x2, 0x2, 0xa5, 0xa3, 0x3, 0x2, 0x2, 0x2, 0xa5, 0xa6, 0x3, 0x2, 
    0x2, 0x2, 0xa6, 0xa9, 0x3, 0x2, 0x2, 0x2, 0xa7, 0xa5, 0x3, 0x2, 0x2, 
    0x2, 0xa8, 0xa1, 0x3, 0x2, 0x2, 0x2, 0xa9, 0xac, 0x3, 0x2, 0x2, 0x2, 
    0xaa, 0xa8, 0x3, 0x2, 0x2, 0x2, 0xaa, 0xab, 0x3, 0x2, 0x2, 0x2, 0xab, 
    0xb6, 0x3, 0x2, 0x2, 0x2, 0xac, 0xaa, 0x3, 0x2, 0x2, 0x2, 0xad, 0xb1, 
    0x5, 0x6, 0x4, 0x2, 0xae, 0xb0, 0x9, 0x2, 0x2, 0x2, 0xaf, 0xae, 0x3, 
    0x2, 0x2, 0x2, 0xb0, 0xb3, 0x3, 0x2, 0x2, 0x2, 0xb1, 0xaf, 0x3, 0x2, 
    0x2, 0x2, 0xb1, 0xb2, 0x3, 0x2, 0x2, 0x2, 0xb2, 0xb5, 0x3, 0x2, 0x2, 
    0x2, 0xb3, 0xb1, 0x3, 0x2, 0x2, 0x2, 0xb4, 0xad, 0x3, 0x2, 0x2, 0x2, 
    0xb5, 0xb8, 0x3, 0x2, 0x2, 0x2, 0xb6, 0xb4, 0x3, 0x2, 0x2, 0x2, 0xb6, 
    0xb7, 0x3, 0x2, 0x2, 0x2, 0xb7, 0xc2, 0x3, 0x2, 0x2, 0x2, 0xb8, 0xb6, 
    0x3, 0x2, 0x2, 0x2, 0xb9, 0xbd, 0x5, 0x8, 0x5, 0x2, 0xba, 0xbc, 0x9, 
    0x2, 0x2, 0x2, 0xbb, 0xba, 0x3, 0x2, 0x2, 0x2, 0xbc, 0xbf, 0x3, 0x2, 
    0x2, 0x2, 0xbd, 0xbb, 0x3, 0x2, 0x2, 0x2, 0xbd, 0xbe, 0x3, 0x2, 0x2, 
    0x2, 0xbe, 0xc1, 0x3, 0x2, 0x2, 0x2, 0xbf, 0xbd, 0x3, 0x2, 0x2, 0x2, 
    0xc0, 0xb9, 0x3, 0x2, 0x2, 0x2, 0xc1, 0xc4, 0x3, 0x2, 0x2, 0x2, 0xc2, 
    0xc0, 0x3, 0x2, 0x2, 0x2, 0xc2, 0xc3, 0x3, 0x2, 0x2, 0x2, 0xc3, 0xce, 
    0x3, 0x2, 0x2, 0x2, 0xc4, 0xc2, 0x3, 0x2, 0x2, 0x2, 0xc5, 0xc9, 0x5, 
    0x64, 0x33, 0x2, 0xc6, 0xc8, 0x9, 0x2, 0x2, 0x2, 0xc7, 0xc6, 0x3, 0x2, 
    0x2, 0x2, 0xc8, 0xcb, 0x3, 0x2, 0x2, 0x2, 0xc9, 0xc7, 0x3, 0x2, 0x2, 
    0x2, 0xc9, 0xca, 0x3, 0x2, 0x2, 0x2, 0xca, 0xcd, 0x3, 0x2, 0x2, 0x2, 
    0xcb, 0xc9, 0x3, 0x2, 0x2, 0x2, 0xcc, 0xc5, 0x3, 0x2, 0x2, 0x2, 0xcd, 
    0xd0, 0x3, 0x2, 0x2, 0x2, 0xce, 0xcc, 0x3, 0x2, 0x2, 0x2, 0xce, 0xcf, 
    0x3, 0x2, 0x2, 0x2, 0xcf, 0x3, 0x3, 0x2, 0x2, 0x2, 0xd0, 0xce, 0x3, 
    0x2, 0x2, 0x2, 0xd1, 0xd2, 0x7, 0x1d, 0x2, 0x2, 0xd2, 0xd3, 0x5, 0x9e, 
    0x50, 0x2, 0xd3, 0xd4, 0x7, 0x2e, 0x2, 0x2, 0xd4, 0xd5, 0x5, 0x9e, 0x50, 
    0x2, 0xd5, 0xd6, 0x7, 0x3, 0x2, 0x2, 0xd6, 0xd7, 0x5, 0x9e, 0x50, 0x2, 
    0xd7, 0xde, 0x3, 0x2, 0x2, 0x2, 0xd8, 0xd9, 0x7, 0x1d, 0x2, 0x2, 0xd9, 
    0xda, 0x5, 0x9e, 0x50, 0x2, 0xda, 0xdb, 0x7, 0x2e, 0x2, 0x2, 0xdb, 0xdc, 
    0x5, 0x9e, 0x50, 0x2, 0xdc, 0xde, 0x3, 0x2, 0x2, 0x2, 0xdd, 0xd1, 0x3, 
    0x2, 0x2, 0x2, 0xdd, 0xd8, 0x3, 0x2, 0x2, 0x2, 0xde, 0x5, 0x3, 0x2, 
    0x2, 0x2, 0xdf, 0xe0, 0x7, 0x19, 0x2, 0x2, 0xe0, 0xe1, 0x5, 0x9e, 0x50, 
    0x2, 0xe1, 0xe2, 0x9, 0x3, 0x2, 0x2, 0xe2, 0xe3, 0x5, 0x9e, 0x50, 0x2, 
    0xe3, 0xe4, 0x5, 0xe, 0x8, 0x2, 0xe4, 0xe5, 0x7, 0x3, 0x2, 0x2, 0xe5, 
    0xe6, 0x5, 0x9e, 0x50, 0x2, 0xe6, 0xfa, 0x3, 0x2, 0x2, 0x2, 0xe7, 0xe8, 
    0x7, 0x19, 0x2, 0x2, 0xe8, 0xe9, 0x5, 0x9e, 0x50, 0x2, 0xe9, 0xea, 0x9, 
    0x3, 0x2, 0x2, 0xea, 0xeb, 0x5, 0x9e, 0x50, 0x2, 0xeb, 0xec, 0x7, 0x3, 
    0x2, 0x2, 0xec, 0xed, 0x5, 0x9e, 0x50, 0x2, 0xed, 0xfa, 0x3, 0x2, 0x2, 
    0x2, 0xee, 0xef, 0x7, 0x19, 0x2, 0x2, 0xef, 0xf0, 0x5, 0x9e, 0x50, 0x2, 
    0xf0, 0xf1, 0x9, 0x3, 0x2, 0x2, 0xf1, 0xf2, 0x5, 0x9e, 0x50, 0x2, 0xf2, 
    0xf3, 0x5, 0xe, 0x8, 0x2, 0xf3, 0xfa, 0x3, 0x2, 0x2, 0x2, 0xf4, 0xf5, 
    0x7, 0x19, 0x2, 0x2, 0xf5, 0xf6, 0x5, 0x9e, 0x50, 0x2, 0xf6, 0xf7, 0x9, 
    0x3, 0x2, 0x2, 0xf7, 0xf8, 0x5, 0x9e, 0x50, 0x2, 0xf8, 0xfa, 0x3, 0x2, 
    0x2, 0x2, 0xf9, 0xdf, 0x3, 0x2, 0x2, 0x2, 0xf9, 0xe7, 0x3, 0x2, 0x2, 
    0x2, 0xf9, 0xee, 0x3, 0x2, 0x2, 0x2, 0xf9, 0xf4, 0x3, 0x2, 0x2, 0x2, 
    0xfa, 0x7, 0x3, 0x2, 0x2, 0x2, 0xfb, 0xfc, 0x7, 0x1c, 0x2, 0x2, 0xfc, 
    0x100, 0x5, 0x9e, 0x50, 0x2, 0xfd, 0xfe, 0x5, 0xa, 0x6, 0x2, 0xfe, 0xff, 
    0x5, 0x9e, 0x50, 0x2, 0xff, 0x101, 0x3, 0x2, 0x2, 0x2, 0x100, 0xfd, 
    0x3, 0x2, 0x2, 0x2, 0x100, 0x101, 0x3, 0x2, 0x2, 0x2, 0x101, 0x102, 
    0x3, 0x2, 0x2, 0x2, 0x102, 0x103, 0x9, 0x3, 0x2, 0x2, 0x103, 0x104, 
    0x5, 0x9e, 0x50, 0x2, 0x104, 0x105, 0x7, 0x3, 0x2, 0x2, 0x105, 0x106, 
    0x5, 0x9e, 0x50, 0x2, 0x106, 0x112, 0x3, 0x2, 0x2, 0x2, 0x107, 0x108, 
    0x7, 0x1c, 0x2, 0x2, 0x108, 0x10c, 0x5, 0x9e, 0x50, 0x2, 0x109, 0x10a, 
    0x5, 0xa, 0x6, 0x2, 0x10a, 0x10b, 0x5, 0x9e, 0x50, 0x2, 0x10b, 0x10d, 
    0x3, 0x2, 0x2, 0x2, 0x10c, 0x109, 0x3, 0x2, 0x2, 0x2, 0x10c, 0x10d, 
    0x3, 0x2, 0x2, 0x2, 0x10d, 0x10e, 0x3, 0x2, 0x2, 0x2, 0x10e, 0x10f, 
    0x9, 0x3, 0x2, 0x2, 0x10f, 0x110, 0x5, 0x9e, 0x50, 0x2, 0x110, 0x112, 
    0x3, 0x2, 0x2, 0x2, 0x111, 0xfb, 0x3, 0x2, 0x2, 0x2, 0x111, 0x107, 0x3, 
    0x2, 0x2, 0x2, 0x112, 0x9, 0x3, 0x2, 0x2, 0x2, 0x113, 0x114, 0x5, 0x9c, 
    0x4f, 0x2, 0x114, 0xb, 0x3, 0x2, 0x2, 0x2, 0x115, 0x116, 0x7, 0x1b, 
    0x2, 0x2, 0x116, 0x117, 0x5, 0x9e, 0x50, 0x2, 0x117, 0x118, 0x5, 0xe, 
    0x8, 0x2, 0x118, 0x119, 0x5, 0x66, 0x34, 0x2, 0x119, 0x11a, 0x5, 0x9e, 
    0x50, 0x2, 0x11a, 0xd, 0x3, 0x2, 0x2, 0x2, 0x11b, 0x122, 0x5, 0x10, 
    0x9, 0x2, 0x11c, 0x11d, 0x7, 0x2a, 0x2, 0x2, 0x11d, 0x11e, 0x5, 0x9e, 
    0x50, 0x2, 0x11e, 0x11f, 0x5, 0x10, 0x9, 0x2, 0x11f, 0x121, 0x3, 0x2, 
    0x2, 0x2, 0x120, 0x11c, 0x3, 0x2, 0x2, 0x2, 0x121, 0x124, 0x3, 0x2, 
    0x2, 0x2, 0x122, 0x120, 0x3, 0x2, 0x2, 0x2, 0x122, 0x123, 0x3, 0x2, 
    0x2, 0x2, 0x123, 0x126, 0x3, 0x2, 0x2, 0x2, 0x124, 0x122, 0x3, 0x2, 
    0x2, 0x2, 0x125, 0x11b, 0x3, 0x2, 0x2, 0x2, 0x125, 0x126, 0x3, 0x2, 
    0x2, 0x2, 0x126, 0x127, 0x3, 0x2, 0x2, 0x2, 0x127, 0x128, 0x5, 0x9e, 
    0x50, 0x2, 0x128, 0xf, 0x3, 0x2, 0x2, 0x2, 0x129, 0x12b, 0x9, 0x4, 0x2, 
    0x2, 0x12a, 0x129, 0x3, 0x2, 0x2, 0x2, 0x12a, 0x12b, 0x3, 0x2, 0x2, 
    0x2, 0x12b, 0x12c, 0x3, 0x2, 0x2, 0x2, 0x12c, 0x12d, 0x5, 0x9e, 0x50, 
    0x2, 0x12d, 0x12e, 0x5, 0x12, 0xa, 0x2, 0x12e, 0x135, 0x5, 0x9e, 0x50, 
    0x2, 0x12f, 0x130, 0x7, 0x24, 0x2, 0x2, 0x130, 0x131, 0x5, 0x9e, 0x50, 
    0x2, 0x131, 0x132, 0x5, 0x14, 0xb, 0x2, 0x132, 0x134, 0x3, 0x2, 0x2, 
    0x2, 0x133, 0x12f, 0x3, 0x2, 0x2, 0x2, 0x134, 0x137, 0x3, 0x2, 0x2, 
    0x2, 0x135, 0x133, 0x3, 0x2, 0x2, 0x2, 0x135, 0x136, 0x3, 0x2, 0x2, 
    0x2, 0x136, 0x143, 0x3, 0x2, 0x2, 0x2, 0x137, 0x135, 0x3, 0x2, 0x2, 
    0x2, 0x138, 0x13f, 0x5, 0x14, 0xb, 0x2, 0x139, 0x13a, 0x7, 0x24, 0x2, 
    0x2, 0x13a, 0x13b, 0x5, 0x9e, 0x50, 0x2, 0x13b, 0x13c, 0x5, 0x14, 0xb, 
    0x2, 0x13c, 0x13e, 0x3, 0x2, 0x2, 0x2, 0x13d, 0x139, 0x3, 0x2, 0x2, 
    0x2, 0x13e, 0x141, 0x3, 0x2, 0x2, 0x2, 0x13f, 0x13d, 0x3, 0x2, 0x2, 
    0x2, 0x13f, 0x140, 0x3, 0x2, 0x2, 0x2, 0x140, 0x143, 0x3, 0x2, 0x2, 
    0x2, 0x141, 0x13f, 0x3, 0x2, 0x2, 0x2, 0x142, 0x12a, 0x3, 0x2, 0x2, 
    0x2, 0x142, 0x138, 0x3, 0x2, 0x2, 0x2, 0x143, 0x11, 0x3, 0x2, 0x2, 0x2, 
    0x144, 0x145, 0x5, 0x9c, 0x4f, 0x2, 0x145, 0x13, 0x3, 0x2, 0x2, 0x2, 
    0x146, 0x147, 0x7, 0x4, 0x2, 0x2, 0x147, 0x148, 0x5, 0x9e, 0x50, 0x2, 
    0x148, 0x14d, 0x5, 0x16, 0xc, 0x2, 0x149, 0x14a, 0x7, 0x5, 0x2, 0x2, 
    0x14a, 0x14b, 0x5, 0x9e, 0x50, 0x2, 0x14b, 0x14c, 0x5, 0x48, 0x25, 0x2, 
    0x14c, 0x14e, 0x3, 0x2, 0x2, 0x2, 0x14d, 0x149, 0x3, 0x2, 0x2, 0x2, 
    0x14d, 0x14e, 0x3, 0x2, 0x2, 0x2, 0x14e, 0x14f, 0x3, 0x2, 0x2, 0x2, 
    0x14f, 0x150, 0x7, 0x6, 0x2, 0x2, 0x150, 0x151, 0x5, 0x9e, 0x50, 0x2, 
    0x151, 0x15, 0x3, 0x2, 0x2, 0x2, 0x152, 0x153, 0x5, 0x9c, 0x4f, 0x2, 
    0x153, 0x154, 0x5, 0x9e, 0x50, 0x2, 0x154, 0x17, 0x3, 0x2, 0x2, 0x2, 
    0x155, 0x156, 0x7, 0x1a, 0x2, 0x2, 0x156, 0x158, 0x5, 0x9e, 0x50, 0x2, 
    0x157, 0x159, 0x5, 0x1a, 0xe, 0x2, 0x158, 0x157, 0x3, 0x2, 0x2, 0x2, 
    0x158, 0x159, 0x3, 0x2, 0x2, 0x2, 0x159, 0x15a, 0x3, 0x2, 0x2, 0x2, 
    0x15a, 0x15b, 0x7, 0x7, 0x2, 0x2, 0x15b, 0x15d, 0x5, 0x9e, 0x50, 0x2, 
    0x15c, 0x15e, 0x5, 0x42, 0x22, 0x2, 0x15d, 0x15c, 0x3, 0x2, 0x2, 0x2, 
    0x15d, 0x15e, 0x3, 0x2, 0x2, 0x2, 0x15e, 0x166, 0x3, 0x2, 0x2, 0x2, 
    0x15f, 0x160, 0x7, 0x3, 0x2, 0x2, 0x160, 0x162, 0x5, 0x9e, 0x50, 0x2, 
    0x161, 0x163, 0x5, 0x42, 0x22, 0x2, 0x162, 0x161, 0x3, 0x2, 0x2, 0x2, 
    0x162, 0x163, 0x3, 0x2, 0x2, 0x2, 0x163, 0x165, 0x3, 0x2, 0x2, 0x2, 
    0x164, 0x15f, 0x3, 0x2, 0x2, 0x2, 0x165, 0x168, 0x3, 0x2, 0x2, 0x2, 
    0x166, 0x164, 0x3, 0x2, 0x2, 0x2, 0x166, 0x167, 0x3, 0x2, 0x2, 0x2, 
    0x167, 0x169, 0x3, 0x2, 0x2, 0x2, 0x168, 0x166, 0x3, 0x2, 0x2, 0x2, 
    0x169, 0x16a, 0x7, 0x8, 0x2, 0x2, 0x16a, 0x16b, 0x5, 0x9e, 0x50, 0x2, 
    0x16b, 0x19, 0x3, 0x2, 0x2, 0x2, 0x16c, 0x16d, 0x7, 0x5, 0x2, 0x2, 0x16d, 
    0x16e, 0x5, 0x9c, 0x4f, 0x2, 0x16e, 0x16f, 0x5, 0x9e, 0x50, 0x2, 0x16f, 
    0x1b, 0x3, 0x2, 0x2, 0x2, 0x170, 0x177, 0x5, 0x1e, 0x10, 0x2, 0x171, 
    0x172, 0x7, 0x2a, 0x2, 0x2, 0x172, 0x173, 0x5, 0x9e, 0x50, 0x2, 0x173, 
    0x174, 0x5, 0x1e, 0x10, 0x2, 0x174, 0x176, 0x3, 0x2, 0x2, 0x2, 0x175, 
    0x171, 0x3, 0x2, 0x2, 0x2, 0x176, 0x179, 0x3, 0x2, 0x2, 0x2, 0x177, 
    0x175, 0x3, 0x2, 0x2, 0x2, 0x177, 0x178, 0x3, 0x2, 0x2, 0x2, 0x178, 
    0x1d, 0x3, 0x2, 0x2, 0x2, 0x179, 0x177, 0x3, 0x2, 0x2, 0x2, 0x17a, 0x17b, 
    0x5, 0x22, 0x12, 0x2, 0x17b, 0x182, 0x5, 0x9e, 0x50, 0x2, 0x17c, 0x17d, 
    0x5, 0x20, 0x11, 0x2, 0x17d, 0x17e, 0x5, 0x22, 0x12, 0x2, 0x17e, 0x17f, 
    0x5, 0x9e, 0x50, 0x2, 0x17f, 0x181, 0x3, 0x2, 0x2, 0x2, 0x180, 0x17c, 
    0x3, 0x2, 0x2, 0x2, 0x181, 0x184, 0x3, 0x2, 0x2, 0x2, 0x182, 0x180, 
    0x3, 0x2, 0x2, 0x2, 0x182, 0x183, 0x3, 0x2, 0x2, 0x2, 0x183, 0x1f, 0x3, 
    0x2, 0x2, 0x2, 0x184, 0x182, 0x3, 0x2, 0x2, 0x2, 0x185, 0x186, 0x7, 
    0x27, 0x2, 0x2, 0x186, 0x18e, 0x5, 0x9e, 0x50, 0x2, 0x187, 0x188, 0x7, 
    0x29, 0x2, 0x2, 0x188, 0x18e, 0x5, 0x9e, 0x50, 0x2, 0x189, 0x18a, 0x7, 
    0x2b, 0x2, 0x2, 0x18a, 0x18e, 0x5, 0x9e, 0x50, 0x2, 0x18b, 0x18c, 0x7, 
    0x13, 0x2, 0x2, 0x18c, 0x18e, 0x5, 0x9e, 0x50, 0x2, 0x18d, 0x185, 0x3, 
    0x2, 0x2, 0x2, 0x18d, 0x187, 0x3, 0x2, 0x2, 0x2, 0x18d, 0x189, 0x3, 
    0x2, 0x2, 0x2, 0x18d, 0x18b, 0x3, 0x2, 0x2, 0x2, 0x18e, 0x21, 0x3, 0x2, 
    0x2, 0x2, 0x18f, 0x192, 0x5, 0x24, 0x13, 0x2, 0x190, 0x192, 0x5, 0x2a, 
    0x16, 0x2, 0x191, 0x18f, 0x3, 0x2, 0x2, 0x2, 0x191, 0x190, 0x3, 0x2, 
    0x2, 0x2, 0x192, 0x19a, 0x3, 0x2, 0x2, 0x2, 0x193, 0x199, 0x7, 0x18, 
    0x2, 0x2, 0x194, 0x199, 0x5, 0x2c, 0x17, 0x2, 0x195, 0x199, 0x5, 0x2e, 
    0x18, 0x2, 0x196, 0x199, 0x5, 0x30, 0x19, 0x2, 0x197, 0x199, 0x5, 0x36, 
    0x1c, 0x2, 0x198, 0x193, 0x3, 0x2, 0x2, 0x2, 0x198, 0x194, 0x3, 0x2, 
    0x2, 0x2, 0x198, 0x195, 0x3, 0x2, 0x2, 0x2, 0x198, 0x196, 0x3, 0x2, 
    0x2, 0x2, 0x198, 0x197, 0x3, 0x2, 0x2, 0x2, 0x199, 0x19c, 0x3, 0x2, 
    0x2, 0x2, 0x19a, 0x198, 0x3, 0x2, 0x2, 0x2, 0x19a, 0x19b, 0x3, 0x2, 
    0x2, 0x2, 0x19b, 0x1a7, 0x3, 0x2, 0x2, 0x2, 0x19c, 0x19a, 0x3, 0x2, 
    0x2, 0x2, 0x19d, 0x1a3, 0x7, 0x18, 0x2, 0x2, 0x19e, 0x1a3, 0x5, 0x2c, 
    0x17, 0x2, 0x19f, 0x1a3, 0x5, 0x2e, 0x18, 0x2, 0x1a0, 0x1a3, 0x5, 0x30, 
    0x19, 0x2, 0x1a1, 0x1a3, 0x5, 0x36, 0x1c, 0x2, 0x1a2, 0x19d, 0x3, 0x2, 
    0x2, 0x2, 0x1a2, 0x19e, 0x3, 0x2, 0x2, 0x2, 0x1a2, 0x19f, 0x3, 0x2, 
    0x2, 0x2, 0x1a2, 0x1a0, 0x3, 0x2, 0x2, 0x2, 0x1a2, 0x1a1, 0x3, 0x2, 
    0x2, 0x2, 0x1a3, 0x1a4, 0x3, 0x2, 0x2, 0x2, 0x1a4, 0x1a2, 0x3, 0x2, 
    0x2, 0x2, 0x1a4, 0x1a5, 0x3, 0x2, 0x2, 0x2, 0x1a5, 0x1a7, 0x3, 0x2, 
    0x2, 0x2, 0x1a6, 0x191, 0x3, 0x2, 0x2, 0x2, 0x1a6, 0x1a2, 0x3, 0x2, 
    0x2, 0x2, 0x1a7, 0x23, 0x3, 0x2, 0x2, 0x2, 0x1a8, 0x1aa, 0x5, 0x26, 
    0x14, 0x2, 0x1a9, 0x1a8, 0x3, 0x2, 0x2, 0x2, 0x1a9, 0x1aa, 0x3, 0x2, 
    0x2, 0x2, 0x1aa, 0x1ab, 0x3, 0x2, 0x2, 0x2, 0x1ab, 0x1ac, 0x5, 0x28, 
    0x15, 0x2, 0x1ac, 0x25, 0x3, 0x2, 0x2, 0x2, 0x1ad, 0x1b0, 0x5, 0x9c, 
    0x4f, 0x2, 0x1ae, 0x1b0, 0x7, 0x9, 0x2, 0x2, 0x1af, 0x1ad, 0x3, 0x2, 
    0x2, 0x2, 0x1af, 0x1ae, 0x3, 0x2, 0x2, 0x2, 0x1af, 0x1b0, 0x3, 0x2, 
    0x2, 0x2, 0x1b0, 0x1b1, 0x3, 0x2, 0x2, 0x2, 0x1b1, 0x1b2, 0x7, 0xa, 
    0x2, 0x2, 0x1b2, 0x27, 0x3, 0x2, 0x2, 0x2, 0x1b3, 0x1b4, 0x5, 0x9c, 
    0x4f, 0x2, 0x1b4, 0x29, 0x3, 0x2, 0x2, 0x2, 0x1b5, 0x1b7, 0x5, 0x26, 
    0x14, 0x2, 0x1b6, 0x1b5, 0x3, 0x2, 0x2, 0x2, 0x1b6, 0x1b7, 0x3, 0x2, 
    0x2, 0x2, 0x1b7, 0x1b8, 0x3, 0x2, 0x2, 0x2, 0x1b8, 0x1b9, 0x7, 0x9, 
    0x2, 0x2, 0x1b9, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x1ba, 0x1bb, 0x7, 0xb, 0x2, 
    0x2, 0x1bb, 0x1bc, 0x5, 0x9c, 0x4f, 0x2, 0x1bc, 0x2d, 0x3, 0x2, 0x2, 
    0x2, 0x1bd, 0x1be, 0x7, 0xc, 0x2, 0x2, 0x1be, 0x1c0, 0x5, 0x9e, 0x50, 
    0x2, 0x1bf, 0x1c1, 0x5, 0x26, 0x14, 0x2, 0x1c0, 0x1bf, 0x3, 0x2, 0x2, 
    0x2, 0x1c0, 0x1c1, 0x3, 0x2, 0x2, 0x2, 0x1c1, 0x1c2, 0x3, 0x2, 0x2, 
    0x2, 0x1c2, 0x1c3, 0x5, 0x9c, 0x4f, 0x2, 0x1c3, 0x1cc, 0x5, 0x9e, 0x50, 
    0x2, 0x1c4, 0x1c5, 0x9, 0x5, 0x2, 0x2, 0x1c5, 0x1c8, 0x5, 0x9e, 0x50, 
    0x2, 0x1c6, 0x1c9, 0x5, 0x9c, 0x4f, 0x2, 0x1c7, 0x1c9, 0x7, 0x2e, 0x2, 
    0x2, 0x1c8, 0x1c6, 0x3, 0x2, 0x2, 0x2, 0x1c8, 0x1c7, 0x3, 0x2, 0x2, 
    0x2, 0x1c9, 0x1ca, 0x3, 0x2, 0x2, 0x2, 0x1ca, 0x1cb, 0x5, 0x9e, 0x50, 
    0x2, 0x1cb, 0x1cd, 0x3, 0x2, 0x2, 0x2, 0x1cc, 0x1c4, 0x3, 0x2, 0x2, 
    0x2, 0x1cc, 0x1cd, 0x3, 0x2, 0x2, 0x2, 0x1cd, 0x1ce, 0x3, 0x2, 0x2, 
    0x2, 0x1ce, 0x1cf, 0x7, 0xe, 0x2, 0x2, 0x1cf, 0x2f, 0x3, 0x2, 0x2, 0x2, 
    0x1d0, 0x1d2, 0x7, 0x5, 0x2, 0x2, 0x1d1, 0x1d3, 0x7, 0x5, 0x2, 0x2, 
    0x1d2, 0x1d1, 0x3, 0x2, 0x2, 0x2, 0x1d2, 0x1d3, 0x3, 0x2, 0x2, 0x2, 
    0x1d3, 0x1d6, 0x3, 0x2, 0x2, 0x2, 0x1d4, 0x1d7, 0x5, 0x9c, 0x4f, 0x2, 
    0x1d5, 0x1d7, 0x5, 0x32, 0x1a, 0x2, 0x1d6, 0x1d4, 0x3, 0x2, 0x2, 0x2, 
    0x1d6, 0x1d5, 0x3, 0x2, 0x2, 0x2, 0x1d7, 0x31, 0x3, 0x2, 0x2, 0x2, 0x1d8, 
    0x1d9, 0x7, 0x40, 0x2, 0x2, 0x1d9, 0x1da, 0x5, 0x9e, 0x50, 0x2, 0x1da, 
    0x1db, 0x5, 0x34, 0x1b, 0x2, 0x1db, 0x1dc, 0x7, 0x6, 0x2, 0x2, 0x1dc, 
    0x33, 0x3, 0x2, 0x2, 0x2, 0x1dd, 0x1e5, 0x7, 0x27, 0x2, 0x2, 0x1de, 
    0x1e5, 0x7, 0x28, 0x2, 0x2, 0x1df, 0x1e5, 0x7, 0x25, 0x2, 0x2, 0x1e0, 
    0x1e5, 0x7, 0x26, 0x2, 0x2, 0x1e1, 0x1e5, 0x7, 0x2d, 0x2, 0x2, 0x1e2, 
    0x1e5, 0x7, 0x2e, 0x2, 0x2, 0x1e3, 0x1e5, 0x5, 0x9c, 0x4f, 0x2, 0x1e4, 
    0x1dd, 0x3, 0x2, 0x2, 0x2, 0x1e4, 0x1de, 0x3, 0x2, 0x2, 0x2, 0x1e4, 
    0x1df, 0x3, 0x2, 0x2, 0x2, 0x1e4, 0x1e0, 0x3, 0x2, 0x2, 0x2, 0x1e4, 
    0x1e1, 0x3, 0x2, 0x2, 0x2, 0x1e4, 0x1e2, 0x3, 0x2, 0x2, 0x2, 0x1e4, 
    0x1e3, 0x3, 0x2, 0x2, 0x2, 0x1e5, 0x1e6, 0x3, 0x2, 0x2, 0x2, 0x1e6, 
    0x1e8, 0x5, 0x9e, 0x50, 0x2, 0x1e7, 0x1e4, 0x3, 0x2, 0x2, 0x2, 0x1e8, 
    0x1e9, 0x3, 0x2, 0x2, 0x2, 0x1e9, 0x1e7, 0x3, 0x2, 0x2, 0x2, 0x1e9, 
    0x1ea, 0x3, 0x2, 0x2, 0x2, 0x1ea, 0x35, 0x3, 0x2, 0x2, 0x2, 0x1eb, 0x1ec, 
    0x7, 0x2c, 0x2, 0x2, 0x1ec, 0x1ed, 0x5, 0x9e, 0x50, 0x2, 0x1ed, 0x1ee, 
    0x5, 0x38, 0x1d, 0x2, 0x1ee, 0x1ef, 0x5, 0x9e, 0x50, 0x2, 0x1ef, 0x1f0, 
    0x7, 0x6, 0x2, 0x2, 0x1f0, 0x37, 0x3, 0x2, 0x2, 0x2, 0x1f1, 0x1f8, 0x5, 
    0x24, 0x13, 0x2, 0x1f2, 0x1f8, 0x5, 0x2a, 0x16, 0x2, 0x1f3, 0x1f8, 0x7, 
    0x18, 0x2, 0x2, 0x1f4, 0x1f8, 0x5, 0x2c, 0x17, 0x2, 0x1f5, 0x1f8, 0x5, 
    0x2e, 0x18, 0x2, 0x1f6, 0x1f8, 0x5, 0x30, 0x19, 0x2, 0x1f7, 0x1f1, 0x3, 
    0x2, 0x2, 0x2, 0x1f7, 0x1f2, 0x3, 0x2, 0x2, 0x2, 0x1f7, 0x1f3, 0x3, 
    0x2, 0x2, 0x2, 0x1f7, 0x1f4, 0x3, 0x2, 0x2, 0x2, 0x1f7, 0x1f5, 0x3, 
    0x2, 0x2, 0x2, 0x1f7, 0x1f6, 0x3, 0x2, 0x2, 0x2, 0x1f8, 0x39, 0x3, 0x2, 
    0x2, 0x2, 0x1f9, 0x1fa, 0x7, 0xf, 0x2, 0x2, 0x1fa, 0x202, 0x5, 0x9e, 
    0x50, 0x2, 0x1fb, 0x1fc, 0x7, 0x2a, 0x2, 0x2, 0x1fc, 0x202, 0x5, 0x9e, 
    0x50, 0x2, 0x1fd, 0x1fe, 0x7, 0x13, 0x2, 0x2, 0x1fe, 0x202, 0x5, 0x9e, 
    0x50, 0x2, 0x1ff, 0x200, 0x7, 0xd, 0x2, 0x2, 0x200, 0x202, 0x5, 0x9e, 
    0x50, 0x2, 0x201, 0x1f9, 0x3, 0x2, 0x2, 0x2, 0x201, 0x1fb, 0x3, 0x2, 
    0x2, 0x2, 0x201, 0x1fd, 0x3, 0x2, 0x2, 0x2, 0x201, 0x1ff, 0x3, 0x2, 
    0x2, 0x2, 0x202, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x203, 0x204, 0x5, 0x9c, 
    0x4f, 0x2, 0x204, 0x205, 0x5, 0x9e, 0x50, 0x2, 0x205, 0x20d, 0x3, 0x2, 
    0x2, 0x2, 0x206, 0x207, 0x7, 0x3d, 0x2, 0x2, 0x207, 0x20d, 0x5, 0x9e, 
    0x50, 0x2, 0x208, 0x209, 0x7, 0x9, 0x2, 0x2, 0x209, 0x20d, 0x5, 0x9c, 
    0x4f, 0x2, 0x20a, 0x20b, 0x7, 0x10, 0x2, 0x2, 0x20b, 0x20d, 0x5, 0x9c, 
    0x4f, 0x2, 0x20c, 0x203, 0x3, 0x2, 0x2, 0x2, 0x20c, 0x206, 0x3, 0x2, 
    0x2, 0x2, 0x20c, 0x208, 0x3, 0x2, 0x2, 0x2, 0x20c, 0x20a, 0x3, 0x2, 
    0x2, 0x2, 0x20d, 0x3d, 0x3, 0x2, 0x2, 0x2, 0x20e, 0x20f, 0x5, 0x1c, 
    0xf, 0x2, 0x20f, 0x210, 0x7, 0x7, 0x2, 0x2, 0x210, 0x212, 0x5, 0x9e, 
    0x50, 0x2, 0x211, 0x213, 0x5, 0x40, 0x21, 0x2, 0x212, 0x211, 0x3, 0x2, 
    0x2, 0x2, 0x212, 0x213, 0x3, 0x2, 0x2, 0x2, 0x213, 0x214, 0x3, 0x2, 
    0x2, 0x2, 0x214, 0x215, 0x7, 0x8, 0x2, 0x2, 0x215, 0x216, 0x5, 0x9e, 
    0x50, 0x2, 0x216, 0x226, 0x3, 0x2, 0x2, 0x2, 0x217, 0x219, 0x5, 0x5a, 
    0x2e, 0x2, 0x218, 0x217, 0x3, 0x2, 0x2, 0x2, 0x219, 0x21c, 0x3, 0x2, 
    0x2, 0x2, 0x21a, 0x218, 0x3, 0x2, 0x2, 0x2, 0x21a, 0x21b, 0x3, 0x2, 
    0x2, 0x2, 0x21b, 0x21d, 0x3, 0x2, 0x2, 0x2, 0x21c, 0x21a, 0x3, 0x2, 
    0x2, 0x2, 0x21d, 0x21e, 0x7, 0x7, 0x2, 0x2, 0x21e, 0x220, 0x5, 0x9e, 
    0x50, 0x2, 0x21f, 0x221, 0x5, 0x40, 0x21, 0x2, 0x220, 0x21f, 0x3, 0x2, 
    0x2, 0x2, 0x220, 0x221, 0x3, 0x2, 0x2, 0x2, 0x221, 0x222, 0x3, 0x2, 
    0x2, 0x2, 0x222, 0x223, 0x7, 0x8, 0x2, 0x2, 0x223, 0x224, 0x5, 0x9e, 
    0x50, 0x2, 0x224, 0x226, 0x3, 0x2, 0x2, 0x2, 0x225, 0x20e, 0x3, 0x2, 
    0x2, 0x2, 0x225, 0x21a, 0x3, 0x2, 0x2, 0x2, 0x226, 0x3f, 0x3, 0x2, 0x2, 
    0x2, 0x227, 0x228, 0x7, 0x3, 0x2, 0x2, 0x228, 0x22a, 0x5, 0x9e, 0x50, 
    0x2, 0x229, 0x227, 0x3, 0x2, 0x2, 0x2, 0x22a, 0x22d, 0x3, 0x2, 0x2, 
    0x2, 0x22b, 0x229, 0x3, 0x2, 0x2, 0x2, 0x22b, 0x22c, 0x3, 0x2, 0x2, 
    0x2, 0x22c, 0x22e, 0x3, 0x2, 0x2, 0x2, 0x22d, 0x22b, 0x3, 0x2, 0x2, 
    0x2, 0x22e, 0x22f, 0x5, 0x42, 0x22, 0x2, 0x22f, 0x237, 0x5, 0x9e, 0x50, 
    0x2, 0x230, 0x231, 0x7, 0x3, 0x2, 0x2, 0x231, 0x233, 0x5, 0x9e, 0x50, 
    0x2, 0x232, 0x234, 0x5, 0x42, 0x22, 0x2, 0x233, 0x232, 0x3, 0x2, 0x2, 
    0x2, 0x233, 0x234, 0x3, 0x2, 0x2, 0x2, 0x234, 0x236, 0x3, 0x2, 0x2, 
    0x2, 0x235, 0x230, 0x3, 0x2, 0x2, 0x2, 0x236, 0x239, 0x3, 0x2, 0x2, 
    0x2, 0x237, 0x235, 0x3, 0x2, 0x2, 0x2, 0x237, 0x238, 0x3, 0x2, 0x2, 
    0x2, 0x238, 0x41, 0x3, 0x2, 0x2, 0x2, 0x239, 0x237, 0x3, 0x2, 0x2, 0x2, 
    0x23a, 0x23b, 0x5, 0x3c, 0x1f, 0x2, 0x23b, 0x23c, 0x7, 0x5, 0x2, 0x2, 
    0x23c, 0x23d, 0x5, 0x9e, 0x50, 0x2, 0x23d, 0x23f, 0x5, 0x48, 0x25, 0x2, 
    0x23e, 0x240, 0x5, 0x44, 0x23, 0x2, 0x23f, 0x23e, 0x3, 0x2, 0x2, 0x2, 
    0x23f, 0x240, 0x3, 0x2, 0x2, 0x2, 0x240, 0x247, 0x3, 0x2, 0x2, 0x2, 
    0x241, 0x242, 0x5, 0x3c, 0x1f, 0x2, 0x242, 0x243, 0x7, 0x5, 0x2, 0x2, 
    0x243, 0x244, 0x5, 0x9e, 0x50, 0x2, 0x244, 0x245, 0x5, 0x46, 0x24, 0x2, 
    0x245, 0x247, 0x3, 0x2, 0x2, 0x2, 0x246, 0x23a, 0x3, 0x2, 0x2, 0x2, 
    0x246, 0x241, 0x3, 0x2, 0x2, 0x2, 0x247, 0x43, 0x3, 0x2, 0x2, 0x2, 0x248, 
    0x249, 0x7, 0x1e, 0x2, 0x2, 0x249, 0x24a, 0x5, 0x9e, 0x50, 0x2, 0x24a, 
    0x45, 0x3, 0x2, 0x2, 0x2, 0x24b, 0x251, 0x5, 0x5a, 0x2e, 0x2, 0x24c, 
    0x251, 0x5, 0x62, 0x32, 0x2, 0x24d, 0x24e, 0x5, 0x5e, 0x30, 0x2, 0x24e, 
    0x24f, 0x5, 0x9e, 0x50, 0x2, 0x24f, 0x251, 0x3, 0x2, 0x2, 0x2, 0x250, 
    0x24b, 0x3, 0x2, 0x2, 0x2, 0x250, 0x24c, 0x3, 0x2, 0x2, 0x2, 0x250, 
    0x24d, 0x3, 0x2, 0x2, 0x2, 0x251, 0x252, 0x3, 0x2, 0x2, 0x2, 0x252, 
    0x250, 0x3, 0x2, 0x2, 0x2, 0x252, 0x253, 0x3, 0x2, 0x2, 0x2, 0x253, 
    0x47, 0x3, 0x2, 0x2, 0x2, 0x254, 0x25b, 0x5, 0x4a, 0x26, 0x2, 0x255, 
    0x257, 0x5, 0x3a, 0x1e, 0x2, 0x256, 0x255, 0x3, 0x2, 0x2, 0x2, 0x256, 
    0x257, 0x3, 0x2, 0x2, 0x2, 0x257, 0x258, 0x3, 0x2, 0x2, 0x2, 0x258, 
    0x25a, 0x5, 0x4a, 0x26, 0x2, 0x259, 0x256, 0x3, 0x2, 0x2, 0x2, 0x25a, 
    0x25d, 0x3, 0x2, 0x2, 0x2, 0x25b, 0x259, 0x3, 0x2, 0x2, 0x2, 0x25b, 
    0x25c, 0x3, 0x2, 0x2, 0x2, 0x25c, 0x49, 0x3, 0x2, 0x2, 0x2, 0x25d, 0x25b, 
    0x3, 0x2, 0x2, 0x2, 0x25e, 0x25f, 0x5, 0x52, 0x2a, 0x2, 0x25f, 0x260, 
    0x5, 0x9e, 0x50, 0x2, 0x260, 0x279, 0x3, 0x2, 0x2, 0x2, 0x261, 0x262, 
    0x5, 0x54, 0x2b, 0x2, 0x262, 0x263, 0x5, 0x9e, 0x50, 0x2, 0x263, 0x279, 
    0x3, 0x2, 0x2, 0x2, 0x264, 0x265, 0x5, 0x56, 0x2c, 0x2, 0x265, 0x266, 
    0x5, 0x9e, 0x50, 0x2, 0x266, 0x279, 0x3, 0x2, 0x2, 0x2, 0x267, 0x268, 
    0x7, 0x2e, 0x2, 0x2, 0x268, 0x279, 0x5, 0x9e, 0x50, 0x2, 0x269, 0x26a, 
    0x7, 0x21, 0x2, 0x2, 0x26a, 0x279, 0x5, 0x9e, 0x50, 0x2, 0x26b, 0x26c, 
    0x5, 0x9c, 0x4f, 0x2, 0x26c, 0x26d, 0x5, 0x9e, 0x50, 0x2, 0x26d, 0x279, 
    0x3, 0x2, 0x2, 0x2, 0x26e, 0x279, 0x5, 0x78, 0x3d, 0x2, 0x26f, 0x270, 
    0x7, 0x20, 0x2, 0x2, 0x270, 0x279, 0x5, 0x9e, 0x50, 0x2, 0x271, 0x279, 
    0x5, 0x50, 0x29, 0x2, 0x272, 0x279, 0x5, 0x7a, 0x3e, 0x2, 0x273, 0x279, 
    0x5, 0x4c, 0x27, 0x2, 0x274, 0x275, 0x5, 0x58, 0x2d, 0x2, 0x275, 0x276, 
    0x5, 0x9e, 0x50, 0x2, 0x276, 0x279, 0x3, 0x2, 0x2, 0x2, 0x277, 0x279, 
    0x5, 0x4e, 0x28, 0x2, 0x278, 0x25e, 0x3, 0x2, 0x2, 0x2, 0x278, 0x261, 
    0x3, 0x2, 0x2, 0x2, 0x278, 0x264, 0x3, 0x2, 0x2, 0x2, 0x278, 0x267, 
    0x3, 0x2, 0x2, 0x2, 0x278, 0x269, 0x3, 0x2, 0x2, 0x2, 0x278, 0x26b, 
    0x3, 0x2, 0x2, 0x2, 0x278, 0x26e, 0x3, 0x2, 0x2, 0x2, 0x278, 0x26f, 
    0x3, 0x2, 0x2, 0x2, 0x278, 0x271, 0x3, 0x2, 0x2, 0x2, 0x278, 0x272, 
    0x3, 0x2, 0x2, 0x2, 0x278, 0x273, 0x3, 0x2, 0x2, 0x2, 0x278, 0x274, 
    0x3, 0x2, 0x2, 0x2, 0x278, 0x277, 0x3, 0x2, 0x2, 0x2, 0x279, 0x4b, 0x3, 
    0x2, 0x2, 0x2, 0x27a, 0x27b, 0x7, 0x40, 0x2, 0x2, 0x27b, 0x27c, 0x5, 
    0x9e, 0x50, 0x2, 0x27c, 0x27d, 0x5, 0x48, 0x25, 0x2, 0x27d, 0x27e, 0x7, 
    0x6, 0x2, 0x2, 0x27e, 0x27f, 0x5, 0x9e, 0x50, 0x2, 0x27f, 0x4d, 0x3, 
    0x2, 0x2, 0x2, 0x280, 0x281, 0x7, 0x3c, 0x2, 0x2, 0x281, 0x282, 0x5, 
    0x9e, 0x50, 0x2, 0x282, 0x283, 0x5, 0x48, 0x25, 0x2, 0x283, 0x284, 0x7, 
    0x6, 0x2, 0x2, 0x284, 0x285, 0x5, 0x9e, 0x50, 0x2, 0x285, 0x4f, 0x3, 
    0x2, 0x2, 0x2, 0x286, 0x287, 0x7, 0x18, 0x2, 0x2, 0x287, 0x288, 0x5, 
    0x9e, 0x50, 0x2, 0x288, 0x51, 0x3, 0x2, 0x2, 0x2, 0x289, 0x28b, 0x9, 
    0x6, 0x2, 0x2, 0x28a, 0x289, 0x3, 0x2, 0x2, 0x2, 0x28a, 0x28b, 0x3, 
    0x2, 0x2, 0x2, 0x28b, 0x28c, 0x3, 0x2, 0x2, 0x2, 0x28c, 0x28d, 0x7, 
    0x2d, 0x2, 0x2, 0x28d, 0x53, 0x3, 0x2, 0x2, 0x2, 0x28e, 0x290, 0x9, 
    0x6, 0x2, 0x2, 0x28f, 0x28e, 0x3, 0x2, 0x2, 0x2, 0x28f, 0x290, 0x3, 
    0x2, 0x2, 0x2, 0x290, 0x291, 0x3, 0x2, 0x2, 0x2, 0x291, 0x292, 0x7, 
    0x1f, 0x2, 0x2, 0x292, 0x55, 0x3, 0x2, 0x2, 0x2, 0x293, 0x295, 0x9, 
    0x6, 0x2, 0x2, 0x294, 0x293, 0x3, 0x2, 0x2, 0x2, 0x294, 0x295, 0x3, 
    0x2, 0x2, 0x2, 0x295, 0x296, 0x3, 0x2, 0x2, 0x2, 0x296, 0x297, 0x7, 
    0x25, 0x2, 0x2, 0x297, 0x57, 0x3, 0x2, 0x2, 0x2, 0x298, 0x29a, 0x9, 
    0x6, 0x2, 0x2, 0x299, 0x298, 0x3, 0x2, 0x2, 0x2, 0x299, 0x29a, 0x3, 
    0x2, 0x2, 0x2, 0x29a, 0x29b, 0x3, 0x2, 0x2, 0x2, 0x29b, 0x29c, 0x7, 
    0x26, 0x2, 0x2, 0x29c, 0x59, 0x3, 0x2, 0x2, 0x2, 0x29d, 0x29e, 0x5, 
    0x9c, 0x4f, 0x2, 0x29e, 0x29f, 0x5, 0x9e, 0x50, 0x2, 0x29f, 0x2df, 0x3, 
    0x2, 0x2, 0x2, 0x2a0, 0x2a1, 0x5, 0x52, 0x2a, 0x2, 0x2a1, 0x2a2, 0x5, 
    0x9e, 0x50, 0x2, 0x2a2, 0x2df, 0x3, 0x2, 0x2, 0x2, 0x2a3, 0x2a4, 0x5, 
    0x54, 0x2b, 0x2, 0x2a4, 0x2a5, 0x5, 0x9e, 0x50, 0x2, 0x2a5, 0x2df, 0x3, 
    0x2, 0x2, 0x2, 0x2a6, 0x2a7, 0x5, 0x56, 0x2c, 0x2, 0x2a7, 0x2a8, 0x5, 
    0x9e, 0x50, 0x2, 0x2a8, 0x2df, 0x3, 0x2, 0x2, 0x2, 0x2a9, 0x2aa, 0x5, 
    0x58, 0x2d, 0x2, 0x2aa, 0x2ab, 0x5, 0x9e, 0x50, 0x2, 0x2ab, 0x2df, 0x3, 
    0x2, 0x2, 0x2, 0x2ac, 0x2ad, 0x7, 0x2e, 0x2, 0x2, 0x2ad, 0x2df, 0x5, 
    0x9e, 0x50, 0x2, 0x2ae, 0x2af, 0x7, 0x20, 0x2, 0x2, 0x2af, 0x2df, 0x5, 
    0x9e, 0x50, 0x2, 0x2b0, 0x2b1, 0x7, 0x18, 0x2, 0x2, 0x2b1, 0x2df, 0x5, 
    0x9e, 0x50, 0x2, 0x2b2, 0x2b3, 0x7, 0x21, 0x2, 0x2, 0x2b3, 0x2df, 0x5, 
    0x9e, 0x50, 0x2, 0x2b4, 0x2b5, 0x7, 0x16, 0x2, 0x2, 0x2b5, 0x2df, 0x5, 
    0x9e, 0x50, 0x2, 0x2b6, 0x2b7, 0x7, 0x17, 0x2, 0x2, 0x2b7, 0x2df, 0x5, 
    0x9e, 0x50, 0x2, 0x2b8, 0x2b9, 0x7, 0x5, 0x2, 0x2, 0x2b9, 0x2df, 0x5, 
    0x9e, 0x50, 0x2, 0x2ba, 0x2bb, 0x7, 0x40, 0x2, 0x2, 0x2bb, 0x2c0, 0x5, 
    0x9e, 0x50, 0x2, 0x2bc, 0x2bf, 0x5, 0x5a, 0x2e, 0x2, 0x2bd, 0x2bf, 0x5, 
    0x60, 0x31, 0x2, 0x2be, 0x2bc, 0x3, 0x2, 0x2, 0x2, 0x2be, 0x2bd, 0x3, 
    0x2, 0x2, 0x2, 0x2bf, 0x2c2, 0x3, 0x2, 0x2, 0x2, 0x2c0, 0x2be, 0x3, 
    0x2, 0x2, 0x2, 0x2c0, 0x2c1, 0x3, 0x2, 0x2, 0x2, 0x2c1, 0x2c3, 0x3, 
    0x2, 0x2, 0x2, 0x2c2, 0x2c0, 0x3, 0x2, 0x2, 0x2, 0x2c3, 0x2c4, 0x7, 
    0x6, 0x2, 0x2, 0x2c4, 0x2c5, 0x5, 0x9e, 0x50, 0x2, 0x2c5, 0x2df, 0x3, 
    0x2, 0x2, 0x2, 0x2c6, 0x2c7, 0x7, 0x4, 0x2, 0x2, 0x2c7, 0x2cc, 0x5, 
    0x9e, 0x50, 0x2, 0x2c8, 0x2cb, 0x5, 0x5a, 0x2e, 0x2, 0x2c9, 0x2cb, 0x5, 
    0x60, 0x31, 0x2, 0x2ca, 0x2c8, 0x3, 0x2, 0x2, 0x2, 0x2ca, 0x2c9, 0x3, 
    0x2, 0x2, 0x2, 0x2cb, 0x2ce, 0x3, 0x2, 0x2, 0x2, 0x2cc, 0x2ca, 0x3, 
    0x2, 0x2, 0x2, 0x2cc, 0x2cd, 0x3, 0x2, 0x2, 0x2, 0x2cd, 0x2cf, 0x3, 
    0x2, 0x2, 0x2, 0x2ce, 0x2cc, 0x3, 0x2, 0x2, 0x2, 0x2cf, 0x2d0, 0x7, 
    0x6, 0x2, 0x2, 0x2d0, 0x2d1, 0x5, 0x9e, 0x50, 0x2, 0x2d1, 0x2df, 0x3, 
    0x2, 0x2, 0x2, 0x2d2, 0x2d3, 0x7, 0xc, 0x2, 0x2, 0x2d3, 0x2d8, 0x5, 
    0x9e, 0x50, 0x2, 0x2d4, 0x2d7, 0x5, 0x5a, 0x2e, 0x2, 0x2d5, 0x2d7, 0x5, 
    0x60, 0x31, 0x2, 0x2d6, 0x2d4, 0x3, 0x2, 0x2, 0x2, 0x2d6, 0x2d5, 0x3, 
    0x2, 0x2, 0x2, 0x2d7, 0x2da, 0x3, 0x2, 0x2, 0x2, 0x2d8, 0x2d6, 0x3, 
    0x2, 0x2, 0x2, 0x2d8, 0x2d9, 0x3, 0x2, 0x2, 0x2, 0x2d9, 0x2db, 0x3, 
    0x2, 0x2, 0x2, 0x2da, 0x2d8, 0x3, 0x2, 0x2, 0x2, 0x2db, 0x2dc, 0x7, 
    0xe, 0x2, 0x2, 0x2dc, 0x2dd, 0x5, 0x9e, 0x50, 0x2, 0x2dd, 0x2df, 0x3, 
    0x2, 0x2, 0x2, 0x2de, 0x29d, 0x3, 0x2, 0x2, 0x2, 0x2de, 0x2a0, 0x3, 
    0x2, 0x2, 0x2, 0x2de, 0x2a3, 0x3, 0x2, 0x2, 0x2, 0x2de, 0x2a6, 0x3, 
    0x2, 0x2, 0x2, 0x2de, 0x2a9, 0x3, 0x2, 0x2, 0x2, 0x2de, 0x2ac, 0x3, 
    0x2, 0x2, 0x2, 0x2de, 0x2ae, 0x3, 0x2, 0x2, 0x2, 0x2de, 0x2b0, 0x3, 
    0x2, 0x2, 0x2, 0x2de, 0x2b2, 0x3, 0x2, 0x2, 0x2, 0x2de, 0x2b4, 0x3, 
    0x2, 0x2, 0x2, 0x2de, 0x2b6, 0x3, 0x2, 0x2, 0x2, 0x2de, 0x2b8, 0x3, 
    0x2, 0x2, 0x2, 0x2de, 0x2ba, 0x3, 0x2, 0x2, 0x2, 0x2de, 0x2c6, 0x3, 
    0x2, 0x2, 0x2, 0x2de, 0x2d2, 0x3, 0x2, 0x2, 0x2, 0x2df, 0x5b, 0x3, 0x2, 
    0x2, 0x2, 0x2e0, 0x2e1, 0x5, 0x5e, 0x30, 0x2, 0x2e1, 0x2e5, 0x5, 0x9e, 
    0x50, 0x2, 0x2e2, 0x2e4, 0x5, 0x5a, 0x2e, 0x2, 0x2e3, 0x2e2, 0x3, 0x2, 
    0x2, 0x2, 0x2e4, 0x2e7, 0x3, 0x2, 0x2, 0x2, 0x2e5, 0x2e3, 0x3, 0x2, 
    0x2, 0x2, 0x2e5, 0x2e6, 0x3, 0x2, 0x2, 0x2, 0x2e6, 0x2eb, 0x3, 0x2, 
    0x2, 0x2, 0x2e7, 0x2e5, 0x3, 0x2, 0x2, 0x2, 0x2e8, 0x2ec, 0x5, 0x62, 
    0x32, 0x2, 0x2e9, 0x2ea, 0x7, 0x3, 0x2, 0x2, 0x2ea, 0x2ec, 0x5, 0x9e, 
    0x50, 0x2, 0x2eb, 0x2e8, 0x3, 0x2, 0x2, 0x2, 0x2eb, 0x2e9, 0x3, 0x2, 
    0x2, 0x2, 0x2ec, 0x5d, 0x3, 0x2, 0x2, 0x2, 0x2ed, 0x2ee, 0x7, 0x11, 
    0x2, 0x2, 0x2ee, 0x2ef, 0x5, 0x9c, 0x4f, 0x2, 0x2ef, 0x5f, 0x3, 0x2, 
    0x2, 0x2, 0x2f0, 0x2fb, 0x5, 0x62, 0x32, 0x2, 0x2f1, 0x2f2, 0x5, 0x5e, 
    0x30, 0x2, 0x2f2, 0x2f3, 0x5, 0x9e, 0x50, 0x2, 0x2f3, 0x2fb, 0x3, 0x2, 
    0x2, 0x2, 0x2f4, 0x2f5, 0x7, 0x3, 0x2, 0x2, 0x2f5, 0x2fb, 0x5, 0x9e, 
    0x50, 0x2, 0x2f6, 0x2f7, 0x7, 0x14, 0x2, 0x2, 0x2f7, 0x2fb, 0x5, 0x9e, 
    0x50, 0x2, 0x2f8, 0x2f9, 0x7, 0x15, 0x2, 0x2, 0x2f9, 0x2fb, 0x5, 0x9e, 
    0x50, 0x2, 0x2fa, 0x2f0, 0x3, 0x2, 0x2, 0x2, 0x2fa, 0x2f1, 0x3, 0x2, 
    0x2, 0x2, 0x2fa, 0x2f4, 0x3, 0x2, 0x2, 0x2, 0x2fa, 0x2f6, 0x3, 0x2, 
    0x2, 0x2, 0x2fa, 0x2f8, 0x3, 0x2, 0x2, 0x2, 0x2fb, 0x61, 0x3, 0x2, 0x2, 
    0x2, 0x2fc, 0x2fd, 0x7, 0x7, 0x2, 0x2, 0x2fd, 0x309, 0x5, 0x9e, 0x50, 
    0x2, 0x2fe, 0x308, 0x5, 0x40, 0x21, 0x2, 0x2ff, 0x308, 0x5, 0x64, 0x33, 
    0x2, 0x300, 0x308, 0x5, 0x5a, 0x2e, 0x2, 0x301, 0x308, 0x5, 0x62, 0x32, 
    0x2, 0x302, 0x303, 0x5, 0x5e, 0x30, 0x2, 0x303, 0x304, 0x5, 0x9e, 0x50, 
    0x2, 0x304, 0x308, 0x3, 0x2, 0x2, 0x2, 0x305, 0x306, 0x7, 0x3, 0x2, 
    0x2, 0x306, 0x308, 0x5, 0x9e, 0x50, 0x2, 0x307, 0x2fe, 0x3, 0x2, 0x2, 
    0x2, 0x307, 0x2ff, 0x3, 0x2, 0x2, 0x2, 0x307, 0x300, 0x3, 0x2, 0x2, 
    0x2, 0x307, 0x301, 0x3, 0x2, 0x2, 0x2, 0x307, 0x302, 0x3, 0x2, 0x2, 
    0x2, 0x307, 0x305, 0x3, 0x2, 0x2, 0x2, 0x308, 0x30b, 0x3, 0x2, 0x2, 
    0x2, 0x309, 0x307, 0x3, 0x2, 0x2, 0x2, 0x309, 0x30a, 0x3, 0x2, 0x2, 
    0x2, 0x30a, 0x30c, 0x3, 0x2, 0x2, 0x2, 0x30b, 0x309, 0x3, 0x2, 0x2, 
    0x2, 0x30c, 0x30d, 0x7, 0x8, 0x2, 0x2, 0x30d, 0x30e, 0x5, 0x9e, 0x50, 
    0x2, 0x30e, 0x63, 0x3, 0x2, 0x2, 0x2, 0x30f, 0x31a, 0x5, 0x3e, 0x20, 
    0x2, 0x310, 0x31a, 0x5, 0xc, 0x7, 0x2, 0x311, 0x31a, 0x5, 0x18, 0xd, 
    0x2, 0x312, 0x31a, 0x5, 0x82, 0x42, 0x2, 0x313, 0x31a, 0x5, 0x86, 0x44, 
    0x2, 0x314, 0x31a, 0x5, 0x68, 0x35, 0x2, 0x315, 0x31a, 0x5, 0x8c, 0x47, 
    0x2, 0x316, 0x31a, 0x5, 0x8e, 0x48, 0x2, 0x317, 0x31a, 0x5, 0x90, 0x49, 
    0x2, 0x318, 0x31a, 0x5, 0x5c, 0x2f, 0x2, 0x319, 0x30f, 0x3, 0x2, 0x2, 
    0x2, 0x319, 0x310, 0x3, 0x2, 0x2, 0x2, 0x319, 0x311, 0x3, 0x2, 0x2, 
    0x2, 0x319, 0x312, 0x3, 0x2, 0x2, 0x2, 0x319, 0x313, 0x3, 0x2, 0x2, 
    0x2, 0x319, 0x314, 0x3, 0x2, 0x2, 0x2, 0x319, 0x315, 0x3, 0x2, 0x2, 
    0x2, 0x319, 0x316, 0x3, 0x2, 0x2, 0x2, 0x319, 0x317, 0x3, 0x2, 0x2, 
    0x2, 0x319, 0x318, 0x3, 0x2, 0x2, 0x2, 0x31a, 0x65, 0x3, 0x2, 0x2, 0x2, 
    0x31b, 0x31c, 0x7, 0x7, 0x2, 0x2, 0x31c, 0x320, 0x5, 0x9e, 0x50, 0x2, 
    0x31d, 0x31f, 0x5, 0x64, 0x33, 0x2, 0x31e, 0x31d, 0x3, 0x2, 0x2, 0x2, 
    0x31f, 0x322, 0x3, 0x2, 0x2, 0x2, 0x320, 0x31e, 0x3, 0x2, 0x2, 0x2, 
    0x320, 0x321, 0x3, 0x2, 0x2, 0x2, 0x321, 0x323, 0x3, 0x2, 0x2, 0x2, 
    0x322, 0x320, 0x3, 0x2, 0x2, 0x2, 0x323, 0x324, 0x7, 0x8, 0x2, 0x2, 
    0x324, 0x325, 0x5, 0x9e, 0x50, 0x2, 0x325, 0x67, 0x3, 0x2, 0x2, 0x2, 
    0x326, 0x327, 0x7, 0x33, 0x2, 0x2, 0x327, 0x328, 0x5, 0x9e, 0x50, 0x2, 
    0x328, 0x329, 0x5, 0x6a, 0x36, 0x2, 0x329, 0x32a, 0x5, 0x9e, 0x50, 0x2, 
    0x32a, 0x32b, 0x5, 0x66, 0x34, 0x2, 0x32b, 0x69, 0x3, 0x2, 0x2, 0x2, 
    0x32c, 0x331, 0x5, 0x6e, 0x38, 0x2, 0x32d, 0x331, 0x5, 0x70, 0x39, 0x2, 
    0x32e, 0x331, 0x5, 0x72, 0x3a, 0x2, 0x32f, 0x331, 0x5, 0x6c, 0x37, 0x2, 
    0x330, 0x32c, 0x3, 0x2, 0x2, 0x2, 0x330, 0x32d, 0x3, 0x2, 0x2, 0x2, 
    0x330, 0x32e, 0x3, 0x2, 0x2, 0x2, 0x330, 0x32f, 0x3, 0x2, 0x2, 0x2, 
    0x331, 0x6b, 0x3, 0x2, 0x2, 0x2, 0x332, 0x333, 0x7, 0x4, 0x2, 0x2, 0x333, 
    0x334, 0x5, 0x9e, 0x50, 0x2, 0x334, 0x335, 0x5, 0x6a, 0x36, 0x2, 0x335, 
    0x336, 0x5, 0x9e, 0x50, 0x2, 0x336, 0x337, 0x7, 0x6, 0x2, 0x2, 0x337, 
    0x33b, 0x3, 0x2, 0x2, 0x2, 0x338, 0x33b, 0x5, 0x74, 0x3b, 0x2, 0x339, 
    0x33b, 0x5, 0x76, 0x3c, 0x2, 0x33a, 0x332, 0x3, 0x2, 0x2, 0x2, 0x33a, 
    0x338, 0x3, 0x2, 0x2, 0x2, 0x33a, 0x339, 0x3, 0x2, 0x2, 0x2, 0x33b, 
    0x6d, 0x3, 0x2, 0x2, 0x2, 0x33c, 0x33d, 0x7, 0x23, 0x2, 0x2, 0x33d, 
    0x33e, 0x5, 0x9e, 0x50, 0x2, 0x33e, 0x33f, 0x7, 0x13, 0x2, 0x2, 0x33f, 
    0x340, 0x5, 0x9e, 0x50, 0x2, 0x340, 0x341, 0x5, 0x6c, 0x37, 0x2, 0x341, 
    0x6f, 0x3, 0x2, 0x2, 0x2, 0x342, 0x34c, 0x5, 0x6c, 0x37, 0x2, 0x343, 
    0x344, 0x5, 0x9e, 0x50, 0x2, 0x344, 0x345, 0x7, 0x13, 0x2, 0x2, 0x345, 
    0x346, 0x5, 0x9e, 0x50, 0x2, 0x346, 0x347, 0x7, 0x24, 0x2, 0x2, 0x347, 
    0x348, 0x5, 0x9e, 0x50, 0x2, 0x348, 0x349, 0x7, 0x13, 0x2, 0x2, 0x349, 
    0x34a, 0x5, 0x9e, 0x50, 0x2, 0x34a, 0x34b, 0x5, 0x6c, 0x37, 0x2, 0x34b, 
    0x34d, 0x3, 0x2, 0x2, 0x2, 0x34c, 0x343, 0x3, 0x2, 0x2, 0x2, 0x34d, 
    0x34e, 0x3, 0x2, 0x2, 0x2, 0x34e, 0x34c, 0x3, 0x2, 0x2, 0x2, 0x34e, 
    0x34f, 0x3, 0x2, 0x2, 0x2, 0x34f, 0x71, 0x3, 0x2, 0x2, 0x2, 0x350, 0x35a, 
    0x5, 0x6c, 0x37, 0x2, 0x351, 0x352, 0x5, 0x9e, 0x50, 0x2, 0x352, 0x353, 
    0x7, 0x13, 0x2, 0x2, 0x353, 0x354, 0x5, 0x9e, 0x50, 0x2, 0x354, 0x355, 
    0x7, 0x34, 0x2, 0x2, 0x355, 0x356, 0x5, 0x9e, 0x50, 0x2, 0x356, 0x357, 
    0x7, 0x13, 0x2, 0x2, 0x357, 0x358, 0x5, 0x9e, 0x50, 0x2, 0x358, 0x359, 
    0x5, 0x6c, 0x37, 0x2, 0x359, 0x35b, 0x3, 0x2, 0x2, 0x2, 0x35a, 0x351, 
    0x3, 0x2, 0x2, 0x2, 0x35b, 0x35c, 0x3, 0x2, 0x2, 0x2, 0x35c, 0x35a, 
    0x3, 0x2, 0x2, 0x2, 0x35c, 0x35d, 0x3, 0x2, 0x2, 0x2, 0x35d, 0x73, 0x3, 
    0x2, 0x2, 0x2, 0x35e, 0x35f, 0x7, 0x4, 0x2, 0x2, 0x35f, 0x360, 0x5, 
    0x9e, 0x50, 0x2, 0x360, 0x361, 0x5, 0x42, 0x22, 0x2, 0x361, 0x362, 0x7, 
    0x6, 0x2, 0x2, 0x362, 0x75, 0x3, 0x2, 0x2, 0x2, 0x363, 0x368, 0x9, 0x7, 
    0x2, 0x2, 0x364, 0x367, 0x5, 0x5a, 0x2e, 0x2, 0x365, 0x367, 0x5, 0x60, 
    0x31, 0x2, 0x366, 0x364, 0x3, 0x2, 0x2, 0x2, 0x366, 0x365, 0x3, 0x2, 
    0x2, 0x2, 0x367, 0x36a, 0x3, 0x2, 0x2, 0x2, 0x368, 0x366, 0x3, 0x2, 
    0x2, 0x2, 0x368, 0x369, 0x3, 0x2, 0x2, 0x2, 0x369, 0x36b, 0x3, 0x2, 
    0x2, 0x2, 0x36a, 0x368, 0x3, 0x2, 0x2, 0x2, 0x36b, 0x36c, 0x7, 0x6, 
    0x2, 0x2, 0x36c, 0x77, 0x3, 0x2, 0x2, 0x2, 0x36d, 0x36e, 0x7, 0x3e, 
    0x2, 0x2, 0x36e, 0x36f, 0x5, 0x9e, 0x50, 0x2, 0x36f, 0x370, 0x7, 0x3d, 
    0x2, 0x2, 0x370, 0x371, 0x5, 0x9e, 0x50, 0x2, 0x371, 0x372, 0x7, 0x6, 
    0x2, 0x2, 0x372, 0x373, 0x5, 0x9e, 0x50, 0x2, 0x373, 0x79, 0x3, 0x2, 
    0x2, 0x2, 0x374, 0x375, 0x7, 0x38, 0x2, 0x2, 0x375, 0x376, 0x5, 0x9e, 
    0x50, 0x2, 0x376, 0x377, 0x5, 0x7c, 0x3f, 0x2, 0x377, 0x378, 0x7, 0x6, 
    0x2, 0x2, 0x378, 0x379, 0x5, 0x9e, 0x50, 0x2, 0x379, 0x7b, 0x3, 0x2, 
    0x2, 0x2, 0x37a, 0x385, 0x5, 0x7e, 0x40, 0x2, 0x37b, 0x37c, 0x7, 0x13, 
    0x2, 0x2, 0x37c, 0x37d, 0x5, 0x9e, 0x50, 0x2, 0x37d, 0x37e, 0x9, 0x6, 
    0x2, 0x2, 0x37e, 0x37f, 0x5, 0x9e, 0x50, 0x2, 0x37f, 0x380, 0x7, 0x13, 
    0x2, 0x2, 0x380, 0x381, 0x5, 0x9e, 0x50, 0x2, 0x381, 0x382, 0x5, 0x7e, 
    0x40, 0x2, 0x382, 0x384, 0x3, 0x2, 0x2, 0x2, 0x383, 0x37b, 0x3, 0x2, 
    0x2, 0x2, 0x384, 0x387, 0x3, 0x2, 0x2, 0x2, 0x385, 0x383, 0x3, 0x2, 
    0x2, 0x2, 0x385, 0x386, 0x3, 0x2, 0x2, 0x2, 0x386, 0x7d, 0x3, 0x2, 0x2, 
    0x2, 0x387, 0x385, 0x3, 0x2, 0x2, 0x2, 0x388, 0x394, 0x5, 0x80, 0x41, 
    0x2, 0x389, 0x38a, 0x7, 0x9, 0x2, 0x2, 0x38a, 0x38b, 0x5, 0x9e, 0x50, 
    0x2, 0x38b, 0x38c, 0x5, 0x80, 0x41, 0x2, 0x38c, 0x393, 0x3, 0x2, 0x2, 
    0x2, 0x38d, 0x38e, 0x7, 0xf, 0x2, 0x2, 0x38e, 0x38f, 0x5, 0x9e, 0x50, 
    0x2, 0x38f, 0x390, 0x5, 0x52, 0x2a, 0x2, 0x390, 0x391, 0x5, 0x9e, 0x50, 
    0x2, 0x391, 0x393, 0x3, 0x2, 0x2, 0x2, 0x392, 0x389, 0x3, 0x2, 0x2, 
    0x2, 0x392, 0x38d, 0x3, 0x2, 0x2, 0x2, 0x393, 0x396, 0x3, 0x2, 0x2, 
    0x2, 0x394, 0x392, 0x3, 0x2, 0x2, 0x2, 0x394, 0x395, 0x3, 0x2, 0x2, 
    0x2, 0x395, 0x7f, 0x3, 0x2, 0x2, 0x2, 0x396, 0x394, 0x3, 0x2, 0x2, 0x2, 
    0x397, 0x398, 0x5, 0x52, 0x2a, 0x2, 0x398, 0x399, 0x5, 0x9e, 0x50, 0x2, 
    0x399, 0x3aa, 0x3, 0x2, 0x2, 0x2, 0x39a, 0x39b, 0x5, 0x56, 0x2c, 0x2, 
    0x39b, 0x39c, 0x5, 0x9e, 0x50, 0x2, 0x39c, 0x3aa, 0x3, 0x2, 0x2, 0x2, 
    0x39d, 0x39e, 0x5, 0x58, 0x2d, 0x2, 0x39e, 0x39f, 0x5, 0x9e, 0x50, 0x2, 
    0x39f, 0x3aa, 0x3, 0x2, 0x2, 0x2, 0x3a0, 0x3a1, 0x5, 0x54, 0x2b, 0x2, 
    0x3a1, 0x3a2, 0x5, 0x9e, 0x50, 0x2, 0x3a2, 0x3aa, 0x3, 0x2, 0x2, 0x2, 
    0x3a3, 0x3a4, 0x7, 0x4, 0x2, 0x2, 0x3a4, 0x3a5, 0x5, 0x9e, 0x50, 0x2, 
    0x3a5, 0x3a6, 0x5, 0x7c, 0x3f, 0x2, 0x3a6, 0x3a7, 0x7, 0x6, 0x2, 0x2, 
    0x3a7, 0x3a8, 0x5, 0x9e, 0x50, 0x2, 0x3a8, 0x3aa, 0x3, 0x2, 0x2, 0x2, 
    0x3a9, 0x397, 0x3, 0x2, 0x2, 0x2, 0x3a9, 0x39a, 0x3, 0x2, 0x2, 0x2, 
    0x3a9, 0x39d, 0x3, 0x2, 0x2, 0x2, 0x3a9, 0x3a0, 0x3, 0x2, 0x2, 0x2, 
    0x3a9, 0x3a3, 0x3, 0x2, 0x2, 0x2, 0x3aa, 0x81, 0x3, 0x2, 0x2, 0x2, 0x3ab, 
    0x3ac, 0x7, 0x32, 0x2, 0x2, 0x3ac, 0x3ad, 0x5, 0x9e, 0x50, 0x2, 0x3ad, 
    0x3ae, 0x7, 0x7, 0x2, 0x2, 0x3ae, 0x3b0, 0x5, 0x9e, 0x50, 0x2, 0x3af, 
    0x3b1, 0x5, 0x84, 0x43, 0x2, 0x3b0, 0x3af, 0x3, 0x2, 0x2, 0x2, 0x3b0, 
    0x3b1, 0x3, 0x2, 0x2, 0x2, 0x3b1, 0x3b9, 0x3, 0x2, 0x2, 0x2, 0x3b2, 
    0x3b3, 0x7, 0x3, 0x2, 0x2, 0x3b3, 0x3b5, 0x5, 0x9e, 0x50, 0x2, 0x3b4, 
    0x3b6, 0x5, 0x84, 0x43, 0x2, 0x3b5, 0x3b4, 0x3, 0x2, 0x2, 0x2, 0x3b5, 
    0x3b6, 0x3, 0x2, 0x2, 0x2, 0x3b6, 0x3b8, 0x3, 0x2, 0x2, 0x2, 0x3b7, 
    0x3b2, 0x3, 0x2, 0x2, 0x2, 0x3b8, 0x3bb, 0x3, 0x2, 0x2, 0x2, 0x3b9, 
    0x3b7, 0x3, 0x2, 0x2, 0x2, 0x3b9, 0x3ba, 0x3, 0x2, 0x2, 0x2, 0x3ba, 
    0x3bc, 0x3, 0x2, 0x2, 0x2, 0x3bb, 0x3b9, 0x3, 0x2, 0x2, 0x2, 0x3bc, 
    0x3bd, 0x7, 0x8, 0x2, 0x2, 0x3bd, 0x3be, 0x5, 0x9e, 0x50, 0x2, 0x3be, 
    0x83, 0x3, 0x2, 0x2, 0x2, 0x3bf, 0x3c0, 0x5, 0x3c, 0x1f, 0x2, 0x3c0, 
    0x3c1, 0x7, 0x5, 0x2, 0x2, 0x3c1, 0x3c2, 0x5, 0x9e, 0x50, 0x2, 0x3c2, 
    0x3c3, 0x5, 0x48, 0x25, 0x2, 0x3c3, 0x3ca, 0x3, 0x2, 0x2, 0x2, 0x3c4, 
    0x3c5, 0x5, 0x3c, 0x1f, 0x2, 0x3c5, 0x3c6, 0x7, 0x5, 0x2, 0x2, 0x3c6, 
    0x3c7, 0x5, 0x9e, 0x50, 0x2, 0x3c7, 0x3c8, 0x5, 0x46, 0x24, 0x2, 0x3c8, 
    0x3ca, 0x3, 0x2, 0x2, 0x2, 0x3c9, 0x3bf, 0x3, 0x2, 0x2, 0x2, 0x3c9, 
    0x3c4, 0x3, 0x2, 0x2, 0x2, 0x3ca, 0x85, 0x3, 0x2, 0x2, 0x2, 0x3cb, 0x3cc, 
    0x7, 0x35, 0x2, 0x2, 0x3cc, 0x3cd, 0x5, 0x9e, 0x50, 0x2, 0x3cd, 0x3ce, 
    0x7, 0x13, 0x2, 0x2, 0x3ce, 0x3cf, 0x5, 0x9e, 0x50, 0x2, 0x3cf, 0x3d0, 
    0x5, 0x9c, 0x4f, 0x2, 0x3d0, 0x3d1, 0x5, 0x9e, 0x50, 0x2, 0x3d1, 0x3d2, 
    0x7, 0x7, 0x2, 0x2, 0x3d2, 0x3d3, 0x5, 0x9e, 0x50, 0x2, 0x3d3, 0x3d4, 
    0x5, 0x88, 0x45, 0x2, 0x3d4, 0x3d5, 0x7, 0x8, 0x2, 0x2, 0x3d5, 0x3d6, 
    0x5, 0x9e, 0x50, 0x2, 0x3d6, 0x87, 0x3, 0x2, 0x2, 0x2, 0x3d7, 0x3d8, 
    0x5, 0x8a, 0x46, 0x2, 0x3d8, 0x3d9, 0x7, 0x7, 0x2, 0x2, 0x3d9, 0x3db, 
    0x5, 0x9e, 0x50, 0x2, 0x3da, 0x3dc, 0x5, 0x40, 0x21, 0x2, 0x3db, 0x3da, 
    0x3, 0x2, 0x2, 0x2, 0x3db, 0x3dc, 0x3, 0x2, 0x2, 0x2, 0x3dc, 0x3dd, 
    0x3, 0x2, 0x2, 0x2, 0x3dd, 0x3de, 0x7, 0x8, 0x2, 0x2, 0x3de, 0x3df, 
    0x5, 0x9e, 0x50, 0x2, 0x3df, 0x3e1, 0x3, 0x2, 0x2, 0x2, 0x3e0, 0x3d7, 
    0x3, 0x2, 0x2, 0x2, 0x3e1, 0x3e4, 0x3, 0x2, 0x2, 0x2, 0x3e2, 0x3e0, 
    0x3, 0x2, 0x2, 0x2, 0x3e2, 0x3e3, 0x3, 0x2, 0x2, 0x2, 0x3e3, 0x89, 0x3, 
    0x2, 0x2, 0x2, 0x3e4, 0x3e2, 0x3, 0x2, 0x2, 0x2, 0x3e5, 0x3e6, 0x9, 
    0x8, 0x2, 0x2, 0x3e6, 0x3ee, 0x5, 0x9e, 0x50, 0x2, 0x3e7, 0x3e8, 0x7, 
    0x2a, 0x2, 0x2, 0x3e8, 0x3e9, 0x5, 0x9e, 0x50, 0x2, 0x3e9, 0x3ea, 0x9, 
    0x8, 0x2, 0x2, 0x3ea, 0x3eb, 0x5, 0x9e, 0x50, 0x2, 0x3eb, 0x3ed, 0x3, 
    0x2, 0x2, 0x2, 0x3ec, 0x3e7, 0x3, 0x2, 0x2, 0x2, 0x3ed, 0x3f0, 0x3, 
    0x2, 0x2, 0x2, 0x3ee, 0x3ec, 0x3, 0x2, 0x2, 0x2, 0x3ee, 0x3ef, 0x3, 
    0x2, 0x2, 0x2, 0x3ef, 0x8b, 0x3, 0x2, 0x2, 0x2, 0x3f0, 0x3ee, 0x3, 0x2, 
    0x2, 0x2, 0x3f1, 0x3f2, 0x7, 0x39, 0x2, 0x2, 0x3f2, 0x3f3, 0x5, 0x9e, 
    0x50, 0x2, 0x3f3, 0x3f4, 0x7, 0x7, 0x2, 0x2, 0x3f4, 0x3f6, 0x5, 0x9e, 
    0x50, 0x2, 0x3f5, 0x3f7, 0x5, 0x40, 0x21, 0x2, 0x3f6, 0x3f5, 0x3, 0x2, 
    0x2, 0x2, 0x3f6, 0x3f7, 0x3, 0x2, 0x2, 0x2, 0x3f7, 0x3f8, 0x3, 0x2, 
    0x2, 0x2, 0x3f8, 0x3f9, 0x7, 0x8, 0x2, 0x2, 0x3f9, 0x3fa, 0x5, 0x9e, 
    0x50, 0x2, 0x3fa, 0x8d, 0x3, 0x2, 0x2, 0x2, 0x3fb, 0x3fc, 0x7, 0x3a, 
    0x2, 0x2, 0x3fc, 0x3fd, 0x5, 0x9e, 0x50, 0x2, 0x3fd, 0x3fe, 0x5, 0x9c, 
    0x4f, 0x2, 0x3fe, 0x3ff, 0x5, 0x9e, 0x50, 0x2, 0x3ff, 0x400, 0x7, 0x7, 
    0x2, 0x2, 0x400, 0x402, 0x5, 0x9e, 0x50, 0x2, 0x401, 0x403, 0x5, 0x40, 
    0x21, 0x2, 0x402, 0x401, 0x3, 0x2, 0x2, 0x2, 0x402, 0x403, 0x3, 0x2, 
    0x2, 0x2, 0x403, 0x404, 0x3, 0x2, 0x2, 0x2, 0x404, 0x405, 0x7, 0x8, 
    0x2, 0x2, 0x405, 0x406, 0x5, 0x9e, 0x50, 0x2, 0x406, 0x8f, 0x3, 0x2, 
    0x2, 0x2, 0x407, 0x408, 0x7, 0x3b, 0x2, 0x2, 0x408, 0x409, 0x5, 0x9e, 
    0x50, 0x2, 0x409, 0x40a, 0x5, 0x92, 0x4a, 0x2, 0x40a, 0x40b, 0x5, 0x9e, 
    0x50, 0x2, 0x40b, 0x40c, 0x7, 0x7, 0x2, 0x2, 0x40c, 0x410, 0x5, 0x9e, 
    0x50, 0x2, 0x40d, 0x40f, 0x5, 0x96, 0x4c, 0x2, 0x40e, 0x40d, 0x3, 0x2, 
    0x2, 0x2, 0x40f, 0x412, 0x3, 0x2, 0x2, 0x2, 0x410, 0x40e, 0x3, 0x2, 
    0x2, 0x2, 0x410, 0x411, 0x3, 0x2, 0x2, 0x2, 0x411, 0x413, 0x3, 0x2, 
    0x2, 0x2, 0x412, 0x410, 0x3, 0x2, 0x2, 0x2, 0x413, 0x414, 0x7, 0x8, 
    0x2, 0x2, 0x414, 0x415, 0x5, 0x9e, 0x50, 0x2, 0x415, 0x91, 0x3, 0x2, 
    0x2, 0x2, 0x416, 0x41e, 0x5, 0x94, 0x4b, 0x2, 0x417, 0x418, 0x5, 0x9e, 
    0x50, 0x2, 0x418, 0x419, 0x7, 0x2a, 0x2, 0x2, 0x419, 0x41a, 0x5, 0x9e, 
    0x50, 0x2, 0x41a, 0x41b, 0x5, 0x94, 0x4b, 0x2, 0x41b, 0x41d, 0x3, 0x2, 
    0x2, 0x2, 0x41c, 0x417, 0x3, 0x2, 0x2, 0x2, 0x41d, 0x420, 0x3, 0x2, 
    0x2, 0x2, 0x41e, 0x41c, 0x3, 0x2, 0x2, 0x2, 0x41e, 0x41f, 0x3, 0x2, 
    0x2, 0x2, 0x41f, 0x93, 0x3, 0x2, 0x2, 0x2, 0x420, 0x41e, 0x3, 0x2, 0x2, 
    0x2, 0x421, 0x42c, 0x7, 0x2e, 0x2, 0x2, 0x422, 0x428, 0x5, 0x9c, 0x4f, 
    0x2, 0x423, 0x424, 0x5, 0x9e, 0x50, 0x2, 0x424, 0x425, 0x5, 0x9c, 0x4f, 
    0x2, 0x425, 0x427, 0x3, 0x2, 0x2, 0x2, 0x426, 0x423, 0x3, 0x2, 0x2, 
    0x2, 0x427, 0x42a, 0x3, 0x2, 0x2, 0x2, 0x428, 0x426, 0x3, 0x2, 0x2, 
    0x2, 0x428, 0x429, 0x3, 0x2, 0x2, 0x2, 0x429, 0x42c, 0x3, 0x2, 0x2, 
    0x2, 0x42a, 0x428, 0x3, 0x2, 0x2, 0x2, 0x42b, 0x421, 0x3, 0x2, 0x2, 
    0x2, 0x42b, 0x422, 0x3, 0x2, 0x2, 0x2, 0x42c, 0x95, 0x3, 0x2, 0x2, 0x2, 
    0x42d, 0x42e, 0x5, 0x98, 0x4d, 0x2, 0x42e, 0x42f, 0x5, 0x9e, 0x50, 0x2, 
    0x42f, 0x430, 0x7, 0x7, 0x2, 0x2, 0x430, 0x432, 0x5, 0x9e, 0x50, 0x2, 
    0x431, 0x433, 0x5, 0x9a, 0x4e, 0x2, 0x432, 0x431, 0x3, 0x2, 0x2, 0x2, 
    0x432, 0x433, 0x3, 0x2, 0x2, 0x2, 0x433, 0x43c, 0x3, 0x2, 0x2, 0x2, 
    0x434, 0x435, 0x5, 0x9e, 0x50, 0x2, 0x435, 0x436, 0x7, 0x3, 0x2, 0x2, 
    0x436, 0x438, 0x5, 0x9e, 0x50, 0x2, 0x437, 0x439, 0x5, 0x9a, 0x4e, 0x2, 
    0x438, 0x437, 0x3, 0x2, 0x2, 0x2, 0x438, 0x439, 0x3, 0x2, 0x2, 0x2, 
    0x439, 0x43b, 0x3, 0x2, 0x2, 0x2, 0x43a, 0x434, 0x3, 0x2, 0x2, 0x2, 
    0x43b, 0x43e, 0x3, 0x2, 0x2, 0x2, 0x43c, 0x43a, 0x3, 0x2, 0x2, 0x2, 
    0x43c, 0x43d, 0x3, 0x2, 0x2, 0x2, 0x43d, 0x43f, 0x3, 0x2, 0x2, 0x2, 
    0x43e, 0x43c, 0x3, 0x2, 0x2, 0x2, 0x43f, 0x440, 0x7, 0x8, 0x2, 0x2, 
    0x440, 0x441, 0x5, 0x9e, 0x50, 0x2, 0x441, 0x97, 0x3, 0x2, 0x2, 0x2, 
    0x442, 0x443, 0x5, 0x5e, 0x30, 0x2, 0x443, 0x99, 0x3, 0x2, 0x2, 0x2, 
    0x444, 0x445, 0x5, 0x9c, 0x4f, 0x2, 0x445, 0x446, 0x5, 0x9e, 0x50, 0x2, 
    0x446, 0x447, 0x7, 0x5, 0x2, 0x2, 0x447, 0x448, 0x5, 0x9e, 0x50, 0x2, 
    0x448, 0x44e, 0x5, 0x52, 0x2a, 0x2, 0x449, 0x44a, 0x5, 0x9e, 0x50, 0x2, 
    0x44a, 0x44b, 0x5, 0x52, 0x2a, 0x2, 0x44b, 0x44d, 0x3, 0x2, 0x2, 0x2, 
    0x44c, 0x449, 0x3, 0x2, 0x2, 0x2, 0x44d, 0x450, 0x3, 0x2, 0x2, 0x2, 
    0x44e, 0x44c, 0x3, 0x2, 0x2, 0x2, 0x44e, 0x44f, 0x3, 0x2, 0x2, 0x2, 
    0x44f, 0x9b, 0x3, 0x2, 0x2, 0x2, 0x450, 0x44e, 0x3, 0x2, 0x2, 0x2, 0x451, 
    0x452, 0x9, 0x9, 0x2, 0x2, 0x452, 0x9d, 0x3, 0x2, 0x2, 0x2, 0x453, 0x455, 
    0x9, 0xa, 0x2, 0x2, 0x454, 0x453, 0x3, 0x2, 0x2, 0x2, 0x455, 0x458, 
    0x3, 0x2, 0x2, 0x2, 0x456, 0x454, 0x3, 0x2, 0x2, 0x2, 0x456, 0x457, 
    0x3, 0x2, 0x2, 0x2, 0x457, 0x9f, 0x3, 0x2, 0x2, 0x2, 0x458, 0x456, 0x3, 
    0x2, 0x2, 0x2, 0x6c, 0xa5, 0xaa, 0xb1, 0xb6, 0xbd, 0xc2, 0xc9, 0xce, 
    0xdd, 0xf9, 0x100, 0x10c, 0x111, 0x122, 0x125, 0x12a, 0x135, 0x13f, 
    0x142, 0x14d, 0x158, 0x15d, 0x162, 0x166, 0x177, 0x182, 0x18d, 0x191, 
    0x198, 0x19a, 0x1a2, 0x1a4, 0x1a6, 0x1a9, 0x1af, 0x1b6, 0x1c0, 0x1c8, 
    0x1cc, 0x1d2, 0x1d6, 0x1e4, 0x1e9, 0x1f7, 0x201, 0x20c, 0x212, 0x21a, 
    0x220, 0x225, 0x22b, 0x233, 0x237, 0x23f, 0x246, 0x250, 0x252, 0x256, 
    0x25b, 0x278, 0x28a, 0x28f, 0x294, 0x299, 0x2be, 0x2c0, 0x2ca, 0x2cc, 
    0x2d6, 0x2d8, 0x2de, 0x2e5, 0x2eb, 0x2fa, 0x307, 0x309, 0x319, 0x320, 
    0x330, 0x33a, 0x34e, 0x35c, 0x366, 0x368, 0x385, 0x392, 0x394, 0x3a9, 
    0x3b0, 0x3b5, 0x3b9, 0x3c9, 0x3db, 0x3e2, 0x3ee, 0x3f6, 0x402, 0x410, 
    0x41e, 0x428, 0x42b, 0x432, 0x438, 0x43c, 0x44e, 0x456, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

css3Parser::Initializer css3Parser::_init;
