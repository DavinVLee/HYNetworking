//
//  HYViewController.m
//  HYNetworking
//
//  Created by fangyuxi on 03/23/2016.
//  Copyright (c) 2016 fangyuxi. All rights reserved.
//

#import "HYViewController.h"
#import "HYNetworking.h"
#import "HYDelegateRequest.h"

@interface HYViewController ()<HYRequestDelegate>
{
    
}

@property (nonatomic, strong) dispatch_group_t dispatchGroup;

@end

@implementation HYViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor whiteColor];
    
//    for (NSInteger index = 0; index < 1; ++index)
//    {
//        HYSimpleRequest *request = [[HYSimpleRequest alloc] init];
//        request.simpleRequestMethod = HYRequestMethodGet;
//        request.simpleApiUrl = @"/api/system?method=initApp";
//        request.simpleName = @"fangyuxi";
//        
//        [request startWithSuccessHandler:^(HYBaseRequest *request, HYNetworkResponse *response) {
//            
//            
//        } failuerHandler:^(HYBaseRequest *request, HYNetworkResponse *response) {
//            
//        }];
//        
//        [request start];
//    }
    
    HYDelegateRequest *request = [[HYDelegateRequest alloc] init];
    request.delegate = self;
    [request start];
    
    
    //self.dispatchGroup = dispatch_group_create();
//    for (NSInteger index = 0; index < 100; ++index)
//    {
//        
//        
//        //dispatch_group_enter(self.dispatchGroup);
//        
//        dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
//            
//            HYDelegateRequest *request = [[HYDelegateRequest alloc] init];
//            request.delegate = self;
//            [request start];
//        });
//    }
    
//    dispatch_group_notify(self.dispatchGroup, dispatch_get_main_queue(), ^(){
//    
//        NSLog(@"Delegate Request All Finished");
//        
//    });
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

- (void)requestDidFinished:(HYBaseRequest *)request
              withResponse:(HYNetworkResponse *)response
{
    //dispatch_group_leave(self.dispatchGroup);
}

- (void)request:(HYBaseRequest *)request
withErrorResponse:(HYNetworkResponse *)response
{
    //dispatch_group_leave(self.dispatchGroup);
}

@end





