/**
 * Autogenerated by Thrift for /home/fbthrift/thrift/lib/thrift/RocketUpgrade.thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "thrift/lib/thrift/gen-cpp2/RocketUpgrade.h"
#include "thrift/lib/thrift/gen-cpp2/RocketUpgrade.tcc"
#include "thrift/lib/thrift/gen-cpp2/RocketUpgrade_metadata.h"
#include <thrift/lib/cpp2/gen/service_cpp.h>

namespace apache { namespace thrift {
std::unique_ptr<apache::thrift::AsyncProcessor> RocketUpgradeSvIf::getProcessor() {
  return std::make_unique<RocketUpgradeAsyncProcessor>(this);
}


void RocketUpgradeSvIf::upgradeToRocket() {
  apache::thrift::detail::si::throw_app_exn_unimplemented("upgradeToRocket");
}

folly::SemiFuture<folly::Unit> RocketUpgradeSvIf::semifuture_upgradeToRocket() {
  return apache::thrift::detail::si::semifuture([&] {
    return upgradeToRocket();
  });
}

folly::Future<folly::Unit> RocketUpgradeSvIf::future_upgradeToRocket() {
  using Source = apache::thrift::concurrency::ThreadManager::Source;
  auto scope = getRequestContext()->getRequestExecutionScope();
  auto ka = getThreadManager()->getKeepAlive(std::move(scope), Source::INTERNAL);
  return apache::thrift::detail::si::future(semifuture_upgradeToRocket(), std::move(ka));
}

void RocketUpgradeSvIf::async_tm_upgradeToRocket(std::unique_ptr<apache::thrift::HandlerCallback<void>> callback) {
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_upgradeToRocket();
  });
}

void RocketUpgradeSvNull::upgradeToRocket() {
  return;
}



const char* RocketUpgradeAsyncProcessor::getServiceName() {
  return "RocketUpgrade";
}

void RocketUpgradeAsyncProcessor::getServiceMetadata(apache::thrift::metadata::ThriftServiceMetadataResponse& response) {
  ::apache::thrift::detail::md::ServiceMetadata<RocketUpgradeSvIf>::gen(*response.metadata_ref(), *response.context_ref());
}

void RocketUpgradeAsyncProcessor::processSerializedCompressedRequest(apache::thrift::ResponseChannelRequest::UniquePtr req, apache::thrift::SerializedCompressedRequest&& serializedRequest, apache::thrift::protocol::PROTOCOL_TYPES protType, apache::thrift::Cpp2RequestContext* context, folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm) {
  apache::thrift::detail::ap::process(this, std::move(req), std::move(serializedRequest), protType, context, eb, tm);
}

std::shared_ptr<folly::RequestContext> RocketUpgradeAsyncProcessor::getBaseContextForRequest() {
  return iface_->getBaseContextForRequest();
}

const RocketUpgradeAsyncProcessor::ProcessMap& RocketUpgradeAsyncProcessor::getBinaryProtocolProcessMap() {
  return binaryProcessMap_;
}

const RocketUpgradeAsyncProcessor::ProcessMap RocketUpgradeAsyncProcessor::binaryProcessMap_ {
  {"upgradeToRocket", &RocketUpgradeAsyncProcessor::setUpAndProcess_upgradeToRocket<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
};

const RocketUpgradeAsyncProcessor::ProcessMap& RocketUpgradeAsyncProcessor::getCompactProtocolProcessMap() {
  return compactProcessMap_;
}

const RocketUpgradeAsyncProcessor::ProcessMap RocketUpgradeAsyncProcessor::compactProcessMap_ {
  {"upgradeToRocket", &RocketUpgradeAsyncProcessor::setUpAndProcess_upgradeToRocket<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
};

}} // apache::thrift
