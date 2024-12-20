/**
 * @file LspProtocol.h
 * @author liukuan (liukuan22@mails.tsinghua.edu.cn)
 * @brief
 * @version 0.0.0
 * @date 2024-11-25
 *
 * @copyright Copyright (C) 2024 GPLv3
 *
 * @ref source
 * https://github.com/llvm/llvm-project/blob/main/clang-tools-extra/clangd/Protocol.h
 *
 * @ref protocol
 * https://microsoft.github.io/language-server-protocol/
 */

#ifndef LSP_PROTOCOL_H
#define LSP_PROTOCOL_H

#include "LspUri.h"

#include <map>
#include <memory>
#include <tuple>
#include <vector>

/**
 * @brief define the json serialize macro
 *
 */
#define MAP_JSON(...)                                                          \
  {                                                                            \
    j = {__VA_ARGS__};                                                         \
  }
#define MAP_KEY(KEY) {#KEY, value.KEY}
#define MAP_TO(KEY, TO) {KEY, value.TO}
#define MAP_KV(K, ...)                                                         \
  {                                                                            \
    K, { __VA_ARGS__ }                                                         \
  }
#define FROM_KEY(KEY)                                                          \
  if (j.contains(#KEY))                                                        \
    j.at(#KEY).get_to(value.KEY);

#define JSON_Convert_Declaration(Type)                                         \
  void to_json(json &j, const Type &value);                                    \
  void from_json(const json &j, Type &value);

#define JSON_Convert_Definition(Type, TO, FROM)                                \
  void to_json(json &j, const Type &value)                                     \
      TO void from_json(const json &j, Type &value) FROM

const static std::string METHOD_DidOpen = "textDocument/didOpen";
const static std::string METHOD_DidClose = "textDocument/didClose";
const static std::string METHOD_DidChange = "textDocument/didChange";
const static std::string METHOD_Definition = "textDocument/definition";
const static std::string METHOD_Declaration = "textDocument/declaration";
const static std::string METHOD_References = "textDocument/references";
const static std::string METHOD_SemanticTokensFull =
    "textDocument/semanticTokens/full";
const static std::string METHOD_PublishDiagnostics =
    "textDocument/publishDiagnostics";
const static std::string METHOD_Hover = "textDocument/hover";
const static std::string METHOD_SignatureHelp = "textDocument/signatureHelp";
const static std::string METHOD_Completion = "textDocument/completion";

using TextType = string_ref;
using DocumentUri = string_ref;
using ProgressToken = string_ref;

enum class ErrorCode {
  // Defined by JSON RPC.
  ParseError = -32700,
  InvalidRequest = -32600,
  MethodNotFound = -32601,
  InvalidParams = -32602,
  InternalError = -32603,
  ServerNotInitialized = -32002,
  UnknownErrorCode = -32001,
  // Defined by the protocol.
  RequestCancelled = -32800,
};
struct LSPError {
  std::string Message;
  ErrorCode Code;
  static char ID;
  LSPError(std::string Message, ErrorCode Code)
      : Message(std::move(Message)), Code(Code) {}
};
JSON_Convert_Declaration(URIForFile);

enum class TraceLevel {
  Off = 0,
  Messages = 1,
  Verbose = 2,
};
enum class TextDocumentSyncKind {

  None = 0,

  Full = 1,

  Incremental = 2,
};
enum class CompletionItemKind {
  Missing = 0,
  Text = 1,
  Method = 2,
  Function = 3,
  Constructor = 4,
  Field = 5,
  Variable = 6,
  Class = 7,
  Interface = 8,
  Module = 9,
  Property = 10,
  Unit = 11,
  Value = 12,
  Enum = 13,
  Keyword = 14,
  Snippet = 15,
  Color = 16,
  File = 17,
  Reference = 18,
  Folder = 19,
  EnumMember = 20,
  Constant = 21,
  Struct = 22,
  Event = 23,
  Operator = 24,
  TypeParameter = 25,
};
enum class SymbolKind {
  File = 1,
  Module = 2,
  Namespace = 3,
  Package = 4,
  Class = 5,
  Method = 6,
  Property = 7,
  Field = 8,
  Constructor = 9,
  Enum = 10,
  Interface = 11,
  Function = 12,
  Variable = 13,
  Constant = 14,
  String = 15,
  Number = 16,
  Boolean = 17,
  Array = 18,
  Object = 19,
  Key = 20,
  Null = 21,
  EnumMember = 22,
  Struct = 23,
  Event = 24,
  Operator = 25,
  TypeParameter = 26
};
enum class OffsetEncoding {
  UnsupportedEncoding,
  UTF16,
  UTF8,
  UTF32,
};
enum class MarkupKind {
  PlainText,
  Markdown,
};
enum class ResourceOperationKind { Create, Rename, Delete };
enum class FailureHandlingKind {
  Abort,
  Transactional,
  Undo,
  TextOnlyTransactional
};
NLOHMANN_JSON_SERIALIZE_ENUM(OffsetEncoding,
                             {
                                 {OffsetEncoding::UnsupportedEncoding,
                                  "unspported"},
                                 {OffsetEncoding::UTF8, "utf-8"},
                                 {OffsetEncoding::UTF16, "utf-16"},
                                 {OffsetEncoding::UTF32, "utf-32"},
                             })
NLOHMANN_JSON_SERIALIZE_ENUM(MarkupKind,
                             {
                                 {MarkupKind::PlainText, "plaintext"},
                                 {MarkupKind::Markdown, "markdown"},
                             })
NLOHMANN_JSON_SERIALIZE_ENUM(ResourceOperationKind,
                             {{ResourceOperationKind::Create, "create"},
                              {ResourceOperationKind::Rename, "rename"},
                              {ResourceOperationKind::Delete, "dename"}})
NLOHMANN_JSON_SERIALIZE_ENUM(
    FailureHandlingKind,
    {{FailureHandlingKind::Abort, "abort"},
     {FailureHandlingKind::Transactional, "transactional"},
     {FailureHandlingKind::Undo, "undo"},
     {FailureHandlingKind::TextOnlyTransactional, "textOnlyTransactional"}})

struct Position {

  int line = 0;

  int character = 0;
  friend bool operator==(const Position &LHS, const Position &RHS) {
    return std::tie(LHS.line, LHS.character) ==
           std::tie(RHS.line, RHS.character);
  }
  friend bool operator!=(const Position &LHS, const Position &RHS) {
    return !(LHS == RHS);
  }
  friend bool operator<(const Position &LHS, const Position &RHS) {
    return std::tie(LHS.line, LHS.character) <
           std::tie(RHS.line, RHS.character);
  }
  friend bool operator<=(const Position &LHS, const Position &RHS) {
    return std::tie(LHS.line, LHS.character) <=
           std::tie(RHS.line, RHS.character);
  }
};
JSON_Convert_Declaration(Position);

struct Range {

  Position start;

  Position end;

  friend bool operator==(const Range &LHS, const Range &RHS) {
    return std::tie(LHS.start, LHS.end) == std::tie(RHS.start, RHS.end);
  }
  friend bool operator!=(const Range &LHS, const Range &RHS) {
    return !(LHS == RHS);
  }
  friend bool operator<(const Range &LHS, const Range &RHS) {
    return std::tie(LHS.start, LHS.end) < std::tie(RHS.start, RHS.end);
  }
  bool contains(Position Pos) const { return start <= Pos && Pos < end; }
  bool contains(Range Rng) const {
    return start <= Rng.start && Rng.end <= end;
  }
};
JSON_Convert_Declaration(Range);

struct TextDocumentItem {

  DocumentUri uri;

  string_ref languageId;

  int version = 0;

  string_ref text;
};
JSON_Convert_Declaration(TextDocumentItem);

struct TextDocumentIdentifier {

  DocumentUri uri;
};
JSON_Convert_Declaration(TextDocumentIdentifier)

    struct VersionedTextDocumentIdentifier : public TextDocumentIdentifier {
  int version = 0;
};
JSON_Convert_Declaration(VersionedTextDocumentIdentifier);

struct TextDocumentPositionParams {

  TextDocumentIdentifier textDocument;

  Position position;
};
JSON_Convert_Declaration(TextDocumentPositionParams);

struct TextEdit {

  Range range;

  std::string newText;
};
JSON_Convert_Declaration(TextEdit);

struct Location {

  std::string uri;
  Range range;

  friend bool operator==(const Location &LHS, const Location &RHS) {
    return LHS.uri == RHS.uri && LHS.range == RHS.range;
  }
  friend bool operator!=(const Location &LHS, const Location &RHS) {
    return !(LHS == RHS);
  }
  friend bool operator<(const Location &LHS, const Location &RHS) {
    return std::tie(LHS.uri, LHS.range) < std::tie(RHS.uri, RHS.range);
  }
};
JSON_Convert_Declaration(Location);

struct DiagnosticRelatedInformation {

  Location location;

  std::string message;
};
JSON_Convert_Declaration(DiagnosticRelatedInformation);

struct CodeAction;

struct Diagnostic {

  Range range;

  int severity = 0;

  std::string code;

  std::string source;

  std::string message;

  option<std::vector<DiagnosticRelatedInformation>> relatedInformation;

  option<std::string> category;

  option<std::vector<CodeAction>> codeActions;
};
JSON_Convert_Declaration(Diagnostic);

struct MarkupContent {
  MarkupKind kind = MarkupKind::PlainText;
  std::string value;
};
JSON_Convert_Declaration(MarkupContent);

struct WorkDoneProgressParams {
  option<ProgressToken> workDoneToken;
};
JSON_Convert_Declaration(WorkDoneProgressParams);

struct PartialResultParams {

  option<ProgressToken> partialResultToken;
};
JSON_Convert_Declaration(PartialResultParams);

struct CodeActionKind {
  std::vector<std::string> valueSet;
};
JSON_Convert_Declaration(CodeActionKind);

struct CodeActionLiteralSupport {
  CodeActionKind codeActionKind;
};
JSON_Convert_Declaration(CodeActionLiteralSupport);

struct ClientCapabilities {

  std::vector<SymbolKind> WorkspaceSymbolKinds;

  bool DiagnosticFixes = true;

  bool DiagnosticRelatedInformation = true;

  bool DiagnosticCategory = true;

  bool CompletionSnippets = true;

  bool CompletionDeprecated = true;

  bool CompletionFixes = true;

  bool HierarchicalDocumentSymbol = true;

  bool OffsetsInSignatureHelp = true;

  std::vector<CompletionItemKind> CompletionItemKinds;

  CodeActionLiteralSupport CodeActionStructure = {};

  std::vector<OffsetEncoding> offsetEncoding = {OffsetEncoding::UTF8};

  std::vector<MarkupKind> HoverContentFormat = {MarkupKind::PlainText};

  bool ApplyEdit = false;
  bool DocumentChanges = false;
  ClientCapabilities() {
    for (int i = 1; i <= 26; ++i) {
      WorkspaceSymbolKinds.push_back((SymbolKind)i);
    }
    for (int i = 0; i <= 25; ++i) {
      CompletionItemKinds.push_back((CompletionItemKind)i);
    }
  }
};
JSON_Convert_Declaration(ClientCapabilities);

struct ServerCapabilities {
  json capabilities;
  TextDocumentSyncKind textDocumentSync = TextDocumentSyncKind::None;
  bool resolveProvider = false;
  std::vector<std::string> executeCommands;
  std::vector<std::string> signatureHelpTrigger;
  std::vector<std::string> formattingTrigger;
  std::vector<std::string> completionTrigger;
  bool hasProvider(std::string &name) {
    if (capabilities.contains(name)) {
      if (capabilities[name].type() == json::value_t::boolean) {
        return capabilities["name"];
      }
    }
    return false;
  }
};
JSON_Convert_Declaration(ServerCapabilities);

struct ClangdCompileCommand {
  TextType workingDirectory;
  std::vector<TextType> compilationCommand;
};
JSON_Convert_Declaration(ClangdCompileCommand);

struct ConfigurationSettings {
  std::map<std::string, ClangdCompileCommand> compilationDatabaseChanges;
};
JSON_Convert_Declaration(ConfigurationSettings);

struct InitializationOptions {
  ConfigurationSettings configSettings;

  option<TextType> compilationDatabasePath;
  std::vector<TextType> fallbackFlags;

  bool clangdFileStatus = false;
};
JSON_Convert_Declaration(InitializationOptions);

struct InitializeParams {
  unsigned processId = 0;
  ClientCapabilities capabilities;
  option<DocumentUri> rootUri;
  option<TextType> rootPath;
  InitializationOptions initializationOptions;
};
JSON_Convert_Declaration(InitializeParams);

enum class MessageType {

  Error = 1,

  Warning = 2,

  Info = 3,

  Log = 4,
};
struct ShowMessageParams {

  MessageType type = MessageType::Info;

  std::string message;
};
JSON_Convert_Declaration(ShowMessageParams);

struct Registration {
  TextType id;

  TextType method;
};
JSON_Convert_Declaration(Registration);

struct RegistrationParams {
  std::vector<Registration> registrations;
};
JSON_Convert_Declaration(RegistrationParams);

struct UnregistrationParams {
  std::vector<Registration> unregisterations;
};
JSON_Convert_Declaration(UnregistrationParams);

// 3.Document Synchronization struct

struct DidOpenTextDocumentParams {

  TextDocumentItem textDocument;
};
JSON_Convert_Declaration(DidOpenTextDocumentParams);

struct DidCloseTextDocumentParams {

  TextDocumentIdentifier textDocument;
};
JSON_Convert_Declaration(DidCloseTextDocumentParams);

struct TextDocumentContentChangeEvent {

  option<Range> range;

  option<int> rangeLength;

  std::string text;
};
JSON_Convert_Declaration(TextDocumentContentChangeEvent);

struct DidChangeTextDocumentParams {

  TextDocumentIdentifier textDocument;

  std::vector<TextDocumentContentChangeEvent> contentChanges;

  option<bool> wantDiagnostics;
};
JSON_Convert_Declaration(DidChangeTextDocumentParams);

enum class FileChangeType {

  Created = 1,

  Changed = 2,

  Deleted = 3
};
struct FileEvent {

  URIForFile uri;

  FileChangeType type = FileChangeType::Created;
};
JSON_Convert_Declaration(FileEvent)

    struct DidChangeWatchedFilesParams {

  std::vector<FileEvent> changes;
};
JSON_Convert_Declaration(DidChangeWatchedFilesParams);

struct DidChangeConfigurationParams {
  ConfigurationSettings settings;
};
JSON_Convert_Declaration(DidChangeConfigurationParams);

struct DocumentRangeFormattingParams {

  TextDocumentIdentifier textDocument;

  Range range;
};
JSON_Convert_Declaration(DocumentRangeFormattingParams);

struct DocumentOnTypeFormattingParams {

  TextDocumentIdentifier textDocument;

  Position position;

  TextType ch;
};
JSON_Convert_Declaration(DocumentOnTypeFormattingParams);

// 4.Language Feartures struct

struct DeclarationParams : public TextDocumentPositionParams,
                           WorkDoneProgressParams,
                           PartialResultParams {};
JSON_Convert_Declaration(DeclarationParams);

struct DefinitionParams : public TextDocumentPositionParams,
                          WorkDoneProgressParams,
                          PartialResultParams {};
JSON_Convert_Declaration(DefinitionParams);

struct TypeDefinitionParams : public TextDocumentPositionParams,
                              WorkDoneProgressParams,
                              PartialResultParams {};
JSON_Convert_Declaration(TypeDefinitionParams);

struct ImplementationParams : public TextDocumentPositionParams,
                              WorkDoneProgressParams,
                              PartialResultParams {};
JSON_Convert_Declaration(ImplementationParams);

struct ReferenceParams : public TextDocumentPositionParams,
                         WorkDoneProgressParams,
                         PartialResultParams {};
JSON_Convert_Declaration(ReferenceParams);

struct HoverParam : public TextDocumentPositionParams,
                    WorkDoneProgressParams {};
JSON_Convert_Declaration(HoverParam);

struct Hover {

  MarkupContent contents;

  option<Range> range;
};
JSON_Convert_Declaration(Hover);

struct FoldingRangeParams {

  TextDocumentIdentifier textDocument;
};
JSON_Convert_Declaration(FoldingRangeParams);

enum class FoldingRangeKind {
  Comment,
  Imports,
  Region,
};
NLOHMANN_JSON_SERIALIZE_ENUM(FoldingRangeKind,
                             {{FoldingRangeKind::Comment, "comment"},
                              {FoldingRangeKind::Imports, "imports"},
                              {FoldingRangeKind::Region, "region"}})

struct FoldingRange {
  int startLine;
  int startCharacter;
  int endLine;
  int endCharacter;

  FoldingRangeKind kind;
};
JSON_Convert_Declaration(FoldingRange);

struct SelectionRangeParams {

  TextDocumentIdentifier textDocument;
  std::vector<Position> positions;
};
JSON_Convert_Declaration(SelectionRangeParams);

struct SelectionRange {
  Range range;
  std::unique_ptr<SelectionRange> parent;
};
JSON_Convert_Declaration(SelectionRange);

struct SemanticTokensParams : public WorkDoneProgressParams,
                              PartialResultParams {
  TextDocumentIdentifier textDocument;
};
JSON_Convert_Declaration(SemanticTokensParams);

struct DocumentFormattingParams {

  TextDocumentIdentifier textDocument;
};
JSON_Convert_Declaration(DocumentFormattingParams);

struct DocumentSymbolParams {
  TextDocumentIdentifier textDocument;
};
JSON_Convert_Declaration(DocumentSymbolParams);

struct PublishDiagnosticsParams {
  std::string uri;
  std::vector<Diagnostic> diagnostics;
};
JSON_Convert_Declaration(PublishDiagnosticsParams);

struct CodeActionContext {

  std::vector<Diagnostic> diagnostics;
};
JSON_Convert_Declaration(CodeActionContext);

struct CodeActionParams {

  TextDocumentIdentifier textDocument;

  Range range;

  CodeActionContext context;
};
JSON_Convert_Declaration(CodeActionParams);

struct WorkspaceEdit {

  option<std::map<std::string, std::vector<TextEdit>>> changes;
};
JSON_Convert_Declaration(WorkspaceEdit);

struct TweakArgs {

  std::string file;

  Range selection;

  std::string tweakID;
};
JSON_Convert_Declaration(TweakArgs);

struct ExecuteCommandParams {
  std::string command;
  // Arguments
  option<WorkspaceEdit> workspaceEdit;
  option<TweakArgs> tweakArgs;
};
JSON_Convert_Declaration(ExecuteCommandParams);

struct LspCommand : public ExecuteCommandParams {
  std::string title;
};

struct CodeAction {

  std::string title;

  option<std::string> kind;

  option<std::vector<Diagnostic>> diagnostics;

  option<WorkspaceEdit> edit;

  option<LspCommand> command;
};
JSON_Convert_Declaration(CodeAction);

struct SymbolInformation {

  std::string name;

  SymbolKind kind = SymbolKind::Class;

  Location location;

  std::string containerName;
};
JSON_Convert_Declaration(SymbolInformation);

struct SymbolDetails {
  TextType name;
  TextType containerName;

  TextType USR;
  option<TextType> ID;
};

struct WorkspaceSymbolParams {

  TextType query;
};
JSON_Convert_Declaration(WorkspaceSymbolParams);

struct ApplyWorkspaceEditParams {
  WorkspaceEdit edit;
};
JSON_Convert_Declaration(ApplyWorkspaceEditParams);

enum class CompletionTriggerKind {

  Invoked = 1,

  TriggerCharacter = 2,

  TriggerTriggerForIncompleteCompletions = 3
};
struct CompletionContext {

  CompletionTriggerKind triggerKind = CompletionTriggerKind::Invoked;

  option<TextType> triggerCharacter;
};
JSON_Convert_Declaration(CompletionContext)

    struct CompletionParams : TextDocumentPositionParams {
  option<CompletionContext> context;
};
JSON_Convert_Declaration(CompletionContext);

enum class InsertTextFormat {
  Missing = 0,

  PlainText = 1,

  ///

  ///

  Snippet = 2,
};
struct CompletionItem {

  std::string label;

  CompletionItemKind kind = CompletionItemKind::Missing;

  std::string detail;

  std::string documentation;

  std::string sortText;

  std::string filterText;

  std::string insertText;

  InsertTextFormat insertTextFormat = InsertTextFormat::Missing;

  TextEdit textEdit;

  std::vector<TextEdit> additionalTextEdits;

  bool deprecated = false;
};
JSON_Convert_Declaration(CompletionItem);

struct CompletionList {

  bool isIncomplete = false;

  std::vector<CompletionItem> items;
};
JSON_Convert_Declaration(CompletionList);

struct ParameterInformation {

  std::string labelString;

  option<std::pair<unsigned, unsigned>> labelOffsets;

  std::string documentation;
};
JSON_Convert_Declaration(ParameterInformation);

struct SignatureInformation {

  std::string label;

  std::string documentation;

  std::vector<ParameterInformation> parameters;
};
JSON_Convert_Declaration(SignatureInformation);

struct SignatureHelp {

  std::vector<SignatureInformation> signatures;

  int activeSignature = 0;

  int activeParameter = 0;

  Position argListStart;
};
JSON_Convert_Declaration(SignatureHelp);

struct RenameParams {

  TextDocumentIdentifier textDocument;

  Position position;

  std::string newName;
};
JSON_Convert_Declaration(RenameParams);

enum class DocumentHighlightKind { Text = 1, Read = 2, Write = 3 };

struct DocumentHighlight {

  Range range;

  DocumentHighlightKind kind = DocumentHighlightKind::Text;
  friend bool operator<(const DocumentHighlight &LHS,
                        const DocumentHighlight &RHS) {
    int LHSKind = static_cast<int>(LHS.kind);
    int RHSKind = static_cast<int>(RHS.kind);
    return std::tie(LHS.range, LHSKind) < std::tie(RHS.range, RHSKind);
  }
  friend bool operator==(const DocumentHighlight &LHS,
                         const DocumentHighlight &RHS) {
    return LHS.kind == RHS.kind && LHS.range == RHS.range;
  }
};
enum class TypeHierarchyDirection { Children = 0, Parents = 1, Both = 2 };

struct TypeHierarchyParams : public TextDocumentPositionParams {

  int resolve = 0;

  TypeHierarchyDirection direction = TypeHierarchyDirection::Parents;
};
JSON_Convert_Declaration(TypeHierarchyParams);

struct TypeHierarchyItem {

  std::string name;

  option<std::string> detail;

  SymbolKind kind;

  bool deprecated;

  DocumentUri uri;

  Range range;

  Range selectionRange;

  option<std::vector<TypeHierarchyItem>> parents;

  option<std::vector<TypeHierarchyItem>> children;
};

#endif // LSP_PROTOCOL_H
