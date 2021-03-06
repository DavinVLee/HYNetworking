//
//  HYBaseRequestInternal.h
//  MyFirst
//
//  Created by fangyuxi on 16/3/8.
//  Copyright © 2016年 fangyuxi. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "HYBaseRequest.h"
#import "HYBaseRequestPrivate.h"
#import "HYNetworkConfig.h"

NS_ASSUME_NONNULL_BEGIN

@interface HYBaseRequestInternal : NSObject
{

}

+ (HYBaseRequestInternal *)sharedInstance;


@property (nonatomic, strong) HYNetworkConfig *networkConfig;

- (void)sendRequest:(HYBaseRequest *)request;
- (void)cancelRequeset:(HYBaseRequest *)request;
- (void)cancelAllRequest;

- (BOOL)isLoadingRequest:(HYBaseRequest *)request;

@end

NS_ASSUME_NONNULL_END
