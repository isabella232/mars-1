//
// Created by Cpan on 2022/3/10.
//

#include "stn_manager.h"
#include "stn_logic_signal.h"
#include "mars/baseevent/active_logic.h"

//using namespace mars::boot;
using namespace mars::comm;

namespace mars {
namespace stn {

StnManager::StnManager() {
    net_core_ = new NetCore();
//    net_source_ = new NetSource(ActiveLogic::Instance());
}

void StnManager::SetCallback(StnCallback *const _callback) {
    callback_ = _callback;
}

void StnManager::SetLonglinkSvrAddr(const std::string &host, const std::vector<uint16_t> ports, const std::string &debugip) {
    std::vector<std::string> hosts;
    if (!host.empty()) {
        hosts.push_back(host);
    }
    NetSource::SetLongLink(hosts, ports, debugip);
}

void StnManager::SetShortlinkSvrAddr(const uint16_t port, const std::string &debugip) {
    NetSource::SetShortlink(port, debugip);
}

void StnManager::SetDebugIP(const std::string &host, const std::string &ip) {
    NetSource::SetDebugIP(host, ip);
}

void StnManager::SetBackupIPs(const std::string &host, const std::vector<std::string> &iplist) {
    NetSource::SetBackupIPs(host, iplist);
}

bool StnManager::StartTask(const Task &task) {
    net_core_->StartTask(task);
    return true;
}

void StnManager::StopTask(uint32_t taskid) {
    net_core_->StopTask(taskid);
}

bool StnManager::HasTask(uint32_t taskid) {
    bool has_task = false;
    has_task = net_core_->HasTask(taskid);
    return has_task;
}

void StnManager::RedoTasks() {
    net_core_->RedoTasks();
}

void StnManager::TouchTasks() {
    net_core_->TouchTasks();
}

void StnManager::ClearTasks() {
    net_core_->ClearTasks();
}

void StnManager::Reset() {
    delete net_core_;
//    delete net_source_;
}

void StnManager::ResetAndInitEncoderVersion(int _encoder_version) {
    LongLinkEncoder::SetEncoderVersion(_encoder_version);
    delete net_core_;
    net_core_ = new NetCore();
}

void StnManager::SetSignallingStrategy(long _period, long _keepTime) {
    SignallingKeeper::SetStrategy((unsigned int)_period, (unsigned int)_keepTime);
}

void StnManager::KeepSignalling() {
    net_core_->KeepSignal();
}

void StnManager::StopSignalling() {

#ifdef USE_LONG_LINK
    net_core_->StopSignal();
#endif

}

void StnManager::MakesureLonglinkConnected() {

}

bool StnManager::LongLinkIsConnected() {
    return false;
}

uint32_t StnManager::getNoopTaskID() {
    return Task::kNoopTaskID;
}

void StnManager::CreateLonglink_ext(LonglinkConfig &_config) {
    net_core_->CreateLongLink(_config);
}

void StnManager::DestroyLonglink_ext(const std::string &name) {
    net_core_->DestroyLongLink(name);
}

std::vector<std::string> StnManager::GetAllLonglink_ext() {
    return std::vector<std::string>();
}

void StnManager::MarkMainLonglink_ext(const std::string &name) {
    net_core_->MarkMainLonglink_ext(name);
}

bool StnManager::LongLinkIsConnected_ext(const std::string &name) {
    bool res = false;
    res = net_core_->LongLinkIsConnected_ext(name);
    return res;
}

void StnManager::MakesureLonglinkConnected_ext(const std::string &name) {
    net_core_->MakeSureLongLinkConnect_ext(name);
}

} // namespace stn
} // namespace mars
