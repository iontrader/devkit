#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H
#include <Structures.h>
#include <rapidjson/document.h>

inline int PLUGIN_VERSION_API = 148;

class HookTrade {
public:
    virtual ~HookTrade() = default;
    virtual int HookTradeRequestOpen(
        const TradeRecord&,const GroupRecord&,const SymbolRecord&,const AccountRecord&,const MarginLevel&,TradeDiffRecord&
    ){ return RET_OK; }
    virtual int HookTradeProcessOpen(
        const TradeRecord&,const GroupRecord&,const SymbolRecord&,const AccountRecord&,const MarginLevel&,TradeDiffRecord&
    ) { return RET_OK; }
    virtual int HookTradeRequestClose(
        const TradeRecord&,const GroupRecord&,const SymbolRecord&,const AccountRecord&,const MarginLevel&,TradeDiffRecord&
     ){ return RET_OK; }
    virtual int HookTradeProcessClose(
        const TradeRecord&,const GroupRecord&,const SymbolRecord&,const AccountRecord&,const MarginLevel&,TradeDiffRecord&
    ) { return RET_OK; }
    virtual int HookTradeProcessCommision(
        const TradeRecord&,const GroupRecord&,const SymbolRecord&,const AccountRecord&,const MarginLevel&,TradeDiffRecord&
    ) { return RET_OK; }
};

class HookAccount {
public:
    virtual ~HookAccount() = default;
    virtual int HookAccountAdd(const AccountRecord&, const MarginLevel&, AccountDiffRecord&){ return RET_OK; }
    virtual int HookAccountUpdate(const AccountRecord&, const MarginLevel&, AccountDiffRecord&) { return RET_OK; }
    virtual int HookAccountDelete(const AccountRecord&, const MarginLevel&, AccountDiffRecord&){ return RET_OK; }
    virtual int HookAccountLogin(const AccountRecord&) { return RET_OK; }
    virtual int HookAccountLogout(const AccountRecord&) { return RET_OK; }
};

class EventTrade {
public:
    virtual ~EventTrade() = default;
    virtual void OnTradeRequestOpen(const TradeRecord&) {}
    virtual void OnTradeAddDB(const TradeRecord&) {}
    virtual void OnTradeRequestClose(const TradeRecord&) {}
    virtual void OnTradeRequestUpdate(const TradeRecord&) {}
    virtual void OnTradeUpdateDB(const TradeRecord&) {}
    virtual void OnTradeRequestDelete(const TradeRecord&) {}
    virtual void OnTradeDeleteDB(const TradeRecord&) {}
};

class EventSymbol {
public:
    virtual ~EventSymbol() = default;
};

class EventAccount {
public:
    virtual ~EventAccount() = default;
    virtual void OnAccountAdd(const AccountRecord& account) {}
    virtual void OnAccountUpdate(const AccountRecord& account) {}
    virtual void OnAccountDelete(const AccountRecord& account) {}
    virtual void OnAccountLogin(const std::string& ip, ConnectionType type, const AccountRecord& account) {}
    virtual void OnAccountLogout(const std::string& ip, ConnectionType type, const AccountRecord& account) {}
    virtual void OnAccountPasswordChange(const std::string& password, const AccountRecord& account) {}
    virtual void OnAccountSync() {}
};

class EventGroup {
public:
    virtual ~EventGroup() = default;
};

class PluginInterface {
public:
    virtual ~PluginInterface() = default;
    virtual int getApiVersion() const { return PLUGIN_VERSION_API; }
    virtual std::string plugin_name() const { return "Demo plugin"; };
    virtual std::string plugin_description() const { return "Demo plugin"; }
    virtual int CustomAction(rapidjson::Value& req, rapidjson::Value& res, rapidjson::Document::AllocatorType& allocator) { return RET_OK_NONE; }
};

#endif