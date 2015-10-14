//
//  AVIMCommon.h
//  AVOSCloudIM
//
//  Created by Qihe Bian on 12/4/14.
//  Copyright (c) 2014 LeanCloud Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import <AVOSCloud/AVOSCloud.h>

@class AVIMConversation;

extern NSString *AVOSCloudIMErrorDomain;

extern NSInteger const kAVIMErrorInvalidCommand;  //非法的请求命令
extern NSInteger const kAVIMErrorInvalidArguments;  //非法参数
extern NSInteger const kAVIMErrorConversationNotFound;  //会话未找到
extern NSInteger const kAVIMErrorTimeout;  //请求超时
extern NSInteger const kAVIMErrorConnectionLost;  //连接断开
extern NSInteger const kAVIMErrorInvalidData;  //非法数据
extern NSInteger const kAVIMErrorMessageTooLong;  //消息内容太长
extern NSInteger const kAVIMErrorClientNotOpen;  //client 没有打开

/* AVOSCloud IM code key */
FOUNDATION_EXPORT NSString *const kAVIMCodeKey;
/* AVOSCloud IM app code key */
FOUNDATION_EXPORT NSString *const kAVIMAppCodeKey;
/* AVOSCloud IM reason key */
FOUNDATION_EXPORT NSString *const kAVIMReasonKey;

typedef void (^AVIMBooleanResultBlock)(BOOL succeeded, NSError *error);
typedef void (^AVIMIntegerResultBlock)(NSInteger number, NSError *error);
typedef void (^AVIMArrayResultBlock)(NSArray *objects, NSError *error);
typedef void (^AVIMConversationResultBlock)(AVIMConversation *conversation, NSError *error);
