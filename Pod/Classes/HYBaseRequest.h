//
//  HYBaseRequest.h
//  MyFirst
//
//  Created by fangyuxi on 16/3/8.
//  Copyright © 2016年 fangyuxi. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AFNetworking.h"
#import "HYNetworkDefines.h"
#import "HYNetworkResponse.h"
#import "HYNetworkResponseFilterProtocol.h"
#import "HYNetworkParameterDecoratorProtocol.h"
#import "HYNetworkServer.h"

NS_ASSUME_NONNULL_BEGIN

#pragma mark block

@class HYBaseRequest;

typedef void (^HYConstructingBlock)(id<AFMultipartFormData> formData);
typedef void (^HYRequestFinishedSuccessHandler)(HYBaseRequest *request, HYNetworkResponse *response);
typedef void (^HYRequestFinishedFailuerHandler)(HYBaseRequest *request, HYNetworkResponse *response);
typedef void (^HYRequestProgressHandler)(HYBaseRequest *request, int64_t progress);

#pragma mark CallBack Delegate Protocol

@protocol HYBaseRequestProtocol <NSObject>

@required

- (HYRequestMethod)requestMethod;

/**
 *  与HYNetworkConfig里面的baseUrl和参数组成完整的请求url
    原则上apiUrl返回的字符串不应该包含任何参数 应该是:/api/user
 *
 *  @return url string
 */
- (NSString *)apiUrl;

/**
 *  一个请求的唯一标识符，原则上不应该重复，业务层可以区分不同的业务请求
 *  可以在log中体现
 *
 *  @return string
 */
- (NSString *)name;

@optional

/**
 *  完整的url 如果有值，那么会忽略掉HYNetworkConfig里面的baseUrl，也会忽略掉自身的server
    一般为调试用，如果有request实现了fullUrl 请造一个警告
 *
 *  @return url string
 */
- (NSString *)fullUrl;

/**
 *  在HTTP报头添加的自定义参数
 *
 *  @return 字典
 */
- (NSDictionary *)requestHeaderValueDictionary;

/**
 *  超时时间
 *
 *  @return 默认30秒
 */
- (NSTimeInterval)requestTimeoutInterval;

/**
 *  当POST的body
 *
 *  @return 构建Body的block
 */
- (HYConstructingBlock)constructingBodyBlock;

/**
 *  请求参数
    对于GET请求，最终会被拼在URL后面
    对于POST请求，最终会放到Body的参数中
 *
 *  @return 返回字典
 */
- (NSDictionary *)requestArgument;

/**
 *  如果不为空，那么GET请求会变成一个下载请求，将文件下载到这个位置
    请保证中间路径文件夹已经创建，不然会下载失败
 *
 *  @return path
 */
- (NSString *)downloadPath;

/**
 *  这个请求的缓存时间，会覆盖全局的缓存时间
 *
 *  @return NStimeInterval by second
 */
- (NSTimeInterval)cacheMaxAge;

/**
 *  缓存策略 默认 HYRequestCachePolicyNoNeedCache
 *
 *  @return 枚举 HYRequestCachePolicy
 */
- (HYRequestCachePolicy)cachePolicy;
@end



#pragma mark CallBack Delegate Protocol

//回调
@protocol HYRequestDelegate <NSObject>

@optional

- (void)requestDidFinished:(HYBaseRequest *)request
              withResponse:(HYNetworkResponse *)response;

- (void)request:(HYBaseRequest *)request
   withErrorResponse:(HYNetworkResponse *)response;

- (void)request:(HYBaseRequest *)request loadingProgress:(CGFloat)progress;

@end





#pragma mark Validator Protocol

/**
 *  验证返回值和参数 可以指向自己
    如果多个request可以共享一个validator，那么可以单独写一个对象
 */
@protocol HYRequestValidator <NSObject>

@optional

/**
 *  返回一个数据结构，用来验证服务端返回的Json对象种的元素的类型是否和我们客户端解析的类型一致
 *
 *  @return 数组或者字典
 */
- (id)responseDataValidator;

@end


#pragma mark HYBaseRequest Interface

@interface HYBaseRequest : NSObject <HYBaseRequestProtocol>
{


}


@property (nonatomic, weak) __nullable id<HYRequestDelegate> delegate;

/**
 *  通常是自己，如果多个接口validator可以重用，也可以单独定义对象
 */
@property (nonatomic, weak) __nullable id<HYRequestValidator> validator;
/**
 *  服务提供者，如果不提供，那么使用config的默认提供者
 */
@property (nonatomic, strong) HYNetworkServer * __nullable server;

@property (nonatomic, strong) NSDictionary * __nullable userInfo;

/**
 *  debug 此request是否打印log 如果为true 那么不论全局log是否打印，这个request都打印
    如果是false，那么遵循全局设置
 */
@property (nonatomic, assign)BOOL debugMode;

/**
 *  参数和返回值过滤器，如果没有赋值，那么默认使用HYNetworkConfig里面的过滤器
    如果有赋值，会忽略掉config
 */
@property (nonatomic, strong) id<HYNetworkParameterDecoratorProtocol> urlFilter;
@property (nonatomic, strong) id<HYNetworkResponseFilterProtocol> responseFilter;

@property (nonatomic, copy) __nullable HYRequestFinishedSuccessHandler successHandler;
@property (nonatomic, copy) __nullable HYRequestFinishedFailuerHandler failerHandler;
@property (nonatomic, copy) __nullable HYRequestProgressHandler progressHandler;


- (void)start;

- (void)startWithSuccessHandler:(__nullable HYRequestFinishedSuccessHandler)successHandler
                 failuerHandler:(__nullable HYRequestFinishedFailuerHandler)failuerHandler;

- (void)cancel;
- (BOOL)isLoading;


/**
 *  debug 此request是否打印log 如果为true 那么不论全局log是否打印，这个request都打印
    如果是false，那么遵循全局设置
 *
 *  @param request request
 *
 *  @return Bool
 */
- (BOOL)isEqualToRequest:(HYBaseRequest *)request;

/**
 *  真正发起请求的URL 调用start后可用
 */
@property (nonatomic, copy, readonly)NSString *URL;

@end

NS_ASSUME_NONNULL_END
