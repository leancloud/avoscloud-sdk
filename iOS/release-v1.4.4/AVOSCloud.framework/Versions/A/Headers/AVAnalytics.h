//
//  AVAnalytics.h
//  AVOS Cloud
//
//  Created by Zhu Zeng on 6/20/13.
//  Copyright (c) 2013 AVOS. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AVConstants.h"

typedef enum {
    AV_REALTIME = 0,       // 实时发送, debug only
    AV_BATCH = 1,          // 启动发送，当消息数量收集到30条时也会发送
    AV_SENDDAILY = 4,      // 每日发送
    AV_SENDWIFIONLY = 5,   // 仅在WIFI下启动时发送, debug only
    AV_SEND_INTERVAL = 6,  // 按最小间隔发送
    AV_SEND_ON_EXIT = 7    // 退出或进入后台时发送
} AVReportPolicy;

@protocol AVAnalyticsDelegate;
@class CLLocation;

@interface AVAnalytics : NSObject

+ (void)trackAppOpenedWithLaunchOptions:(NSDictionary *)launchOptions;
+ (void)trackAppOpenedWithRemoteNotificationPayload:(NSDictionary *)userInfo;
+ (void)setChannel:(NSString *)channel;



/** AVAnalytics 本身不需要实例化，所有方法以静态方法的形式提供.
 目前发送策略有AV_REALTIME, AV_BATCH, AV_SENDDAILY, AV_SENDWIFIONLY, AV_SEND_INTERVAL, AV_SEND_ON_EXIT。
 其中AV_REALTIME, AV_SENDWIFIONLY 只在模拟器和DEBUG模式下生效，真机release模式会自动改成AV_BATCH。

 AV_SEND_INTERVAL 为按最小间隔发送,默认为10秒,取值范围为10 到 86400(一天)， 如果不在这个区间的话，会按10设置。
 AV_SEND_ON_EXIT 为退出或进入后台时发送,这种发送策略在App运行过程中不发送，对开发者和用户的影响最小。
 不过这种发送策略只在iOS > 4.0时才会生效, iOS < 4.0 会被自动调整为AV_BATCH。
 
 */
#pragma mark basics


/** 开启CrashReport收集, 默认是开启状态.
 
 @param value 设置成NO,就可以关闭CrashReport收集.
 @return void.
 */
+ (void)setCrashReportEnabled:(BOOL)value;


/** 开启CrashReport收集, 并且尝试忽略异常.
 @discuss 当异常被捕获后,如果开启了CrashReport功能,异常会被自动捕获,如果开启ignore,会尝试阻止app崩溃, 如果阻止成功,则会提示(UIAlertView)用户程序可能不稳定,请用户选择继续运行还是退出.
 @warning 这不是解决问题的办法,因为App仍然存在不可控因素,而且忽略异常后会造成CPU的占用率提高5%左右. 所以,请尽量找出引起Crash的原因(AVOSCloud后台的错误报告中已经记录了相关信息),并且修复这个问题.
 
 @param value 设置成NO,就可以关闭CrashReport收集.
 @param ignore 设置成YES,可以尝试忽略异常.
 */

+ (void)setCrashReportEnabled:(BOOL)value andIgnore:(BOOL)ignore;


/** 开启CrashReport收集, 并且尝试忽略异常.
 @discuss 效果等同于`setCrashReportEnabled:andIgnore:` 但是可以自定义弹出提醒的文字内容.
 
 @param value 设置成NO,就可以关闭CrashReport收集.
 @param alertTitle 弹出提醒的标题
 @param alertMsg 弹出提醒的内容
 @param alertQuit `退出`按钮的文字
 @param alertContinue `继续`按钮的文字
 */
+ (void)setCrashReportEnabled:(BOOL)value withIgnoreAlertTitle:(NSString*)alertTitle andMessage:(NSString*)alertMsg andQuitTitle:(NSString*)alertQuit andContinueTitle:(NSString*)alertContinue;


/** 设置是否打印sdk的log信息,默认不开启
 @param value 设置为YES, SDK 会输出log信息,记得release产品时要设置回NO.
 @return .
 @exception .
 */

+ (void)setLogEnabled:(BOOL)value;

/**
 当reportPolicy == AV_SEND_INTERVAL 时设定log发送间隔
 @param second 单位为秒,最小为10,最大为86400(一天).
 @return void.
 */

+ (void)setLogSendInterval:(double)second;


///---------------------------------------------------------------------------------------
/// @name  开启统计
///---------------------------------------------------------------------------------------

/** 开启统计,默认以AV_BATCH方式发送log. 1.4.3以后不再需要，请前往在线配置进行配置。
 https://cn.avoscloud.com/stat.html?appid=YOUR_APP_ID&os=ios#/statconfig/trans_strategoy
  @return void
 */

+ (void)start;

/** 开启统计,默认以AV_BATCH方式发送log. 1.4.3以后不再需要，请前往在线配置进行配置。
 https://cn.avoscloud.com/stat.html?appid=YOUR_APP_ID&os=ios#/statconfig/trans_strategoy
 
 @param reportPolicy 发送策略.
 @param channelId 渠道名称,为nil或@""时,默认会被被当作@"App Store"渠道
 @return void
 */
+ (void)startWithReportPolicy:(AVReportPolicy)rp channelId:(NSString *)cid;

///---------------------------------------------------------------------------------------
/// @name  页面计时
///---------------------------------------------------------------------------------------


/** 页面时长统计,记录某个view被打开多长时间,可以自己计时也可以调用beginLogPageView,endLogPageView自动计时
 
 @param pageName 需要记录时长的view名称.
 @param seconds 秒数，int型.
 @return void.
 */

+ (void)logPageView:(NSString *)pageName seconds:(int)seconds;

/** 页面时长统计,记录页面开始事件。
 @param pageName 需要记录时长的view名称.
 @return void.
 */

+ (void)beginLogPageView:(NSString *)pageName;

/** 页面时长统计,记录页面结束事件。
 @param pageName 需要记录时长的view名称.
 @return void.
 */
+ (void)endLogPageView:(NSString *)pageName;

#pragma mark event logs


///---------------------------------------------------------------------------------------
/// @name  事件统计
///---------------------------------------------------------------------------------------


/** 自定义事件,数量统计.
 @param  eventId 自定义的事件Id.
 @return void.
 */
+ (void)event:(NSString *)eventId;



 /** 自定义事件,数量统计.
 @param  eventId 自定义的事件Id.
 @param  label 分类标签。不同的标签会分别进行统计，方便同一事件的不同标签的对比,为nil或空字符串时后台会生成和eventId同名的标签.
 @return void.
 */
+ (void)event:(NSString *)eventId label:(NSString *)label;

/** 自定义事件,数量统计.
 @param  eventId 自定义的事件Id.
 @param  acc 事件的累计发生次数，可以将相同事件合并在一起发送节省网络流量.
 @return void.
 */
+ (void)event:(NSString *)eventId acc:(NSInteger)accumulation;

/** 自定义事件,数量统计.
 @param  eventId 自定义的事件Id.
 @param  label 分类标签。不同的标签会分别进行统计，方便同一事件的不同标签的对比,为nil或空字符串时后台会生成和eventId同名的标签.
 @param  acc 事件的累计发生次数，可以将相同事件合并在一起发送节省网络流量.
 */
+ (void)event:(NSString *)eventId label:(NSString *)label acc:(NSInteger)accumulation;


 /** 自定义事件,数量统计.
 @param  eventId 自定义的事件Id.
 @param  attributes的key最大为128个bytes(128个英文及数字或42个左右汉字)。attributes的value最大为256个bytes(256个英文及数字或84个左右汉字),
  超过后将被截短。
 */
+ (void)event:(NSString *)eventId attributes:(NSDictionary *)attributes;


/** 自定义事件,时长统计， 记录事件开始。
 @param eventId 自定义事件的Id.
 */
+ (void)beginEvent:(NSString *)eventId;


/** 自定义事件,时长统计，记录事件结束。
 @param eventId 自定义事件的Id.
 */
+ (void)endEvent:(NSString *)eventId;

/** 自定义事件,时长统计， 记录事件开始。
 @param eventId 自定义事件的Id.
 @param  label 分类标签。不同的标签会分别进行统计，方便同一事件的不同标签的对比,为nil或空字符串时后台会生成和eventId同名的标签.
 */
+ (void)beginEvent:(NSString *)eventId label:(NSString *)label;


/** 自定义事件,时长统计， 记录事件结束。
 @param eventId 自定义事件的Id.
 @param  label 分类标签。不同的标签会分别进行统计，方便同一事件的不同标签的对比,为nil或空字符串时后台会生成和eventId同名的标签.
 */
+ (void)endEvent:(NSString *)eventId label:(NSString *)label;

/** 自定义事件,时长统计， 记录事件开始。
 @param eventId 自定义事件的Id.
 @param primarykey 自定义关键事件的标签. 关键事件标签用于区分同名事件，但不参与统计运算结果.
 @param attributes 自定义事件的属性列表.
 */
+ (void)beginEvent:(NSString *)eventId primarykey :(NSString *)keyName attributes:(NSDictionary *)attributes;

/** 自定义事件,时长统计， 记录事件结束。
 @param eventId 自定义事件的Id.
 @param primarykey 自定义关键事件的标签. 关键事件标签用于区分同名事件，但不参与统计运算结果.
 */
+ (void)endEvent:(NSString *)eventId primarykey:(NSString *)keyName;


/** 自定义事件,时长统计.
 @param eventId 自定义事件的Id.
 @param millisecond 自定义事件的持续时间.
 */
+ (void)event:(NSString *)eventId durations:(int)millisecond;

/** 自定义事件,时长统计.
 @param eventId 自定义事件的Id.
 @param  label 分类标签。不同的标签会分别进行统计，方便同一事件的不同标签的对比,为nil或空字符串时后台会生成和eventId同名的标签.
 @param millisecond 自定义事件的持续时间.
 */

+ (void)event:(NSString *)eventId label:(NSString *)label durations:(int)millisecond;

/** 自定义事件,时长统计.
 @param eventId 自定义事件的Id.
 @param attributes 自定义事件的属性列表.
 @param millisecond 自定义事件的持续时间.
 */
+ (void)event:(NSString *)eventId attributes:(NSDictionary *)attributes durations:(int)millisecond;



///---------------------------------------------------------------------------------------
/// @name  在线参数
///---------------------------------------------------------------------------------------


/** 使用在线参数功能，可以让你动态修改应用中的参数值,
 检查并更新服务器端配置的在线参数,缓存在[NSUserDefaults standardUserDefaults]里,
 调用此方法您将自动拥有在线更改SDK端发送策略的功能,您需要先在服务器端设置好在线参数.
 请在[AVAnalytics start]方法之后调用;
 @param 无.
 @return void.
 */

+ (void)updateOnlineConfig;

/** 使用在线参数功能，可以让你动态修改应用中的参数值,
 检查并更新服务器端配置的在线参数,缓存在[NSUserDefaults standardUserDefaults]里,
 调用此方法您将自动拥有在线更改SDK端发送策略的功能,您需要先在服务器端设置好在线参数.
 请在[AVAnalytics start]方法之后调用;
 @param block 自定义的接收block，您的配置参数会通过block传给您的应用.
 @return void.
 */
+ (void)updateOnlineConfigWithBlock:(AVDictionaryResultBlock)block;


/** 从[NSUserDefaults standardUserDefaults]获取缓存的在线参数的数值
 带参数的方法获取某个key的值，不带参数的获取所有的在线参数.
 需要先调用updateOnlineConfig才能使用
 
 @param key
 @return (NSString *) .
 */

+ (NSString *)getConfigParams:(NSString *)key;

/** 从[NSUserDefaults standardUserDefaults]获取缓存的在线参数
 @return (NSDictionary *).
 */

+ (NSDictionary *)getConfigParams;


///---------------------------------------------------------------------------------------
/// @name 地理位置设置
///---------------------------------------------------------------------------------------


/** 为了更精确的统计用户地理位置，可以调用此方法传入经纬度信息
 需要链接 CoreLocation.framework 并且 #import <CoreLocation/CoreLocation.h>
 @param latitude 纬度.
 @param longitude 经度.
 
 @return void
 */

+ (void)setLatitude:(double)latitude longitude:(double)longitude;

/** 为了更精确的统计用户地理位置，可以调用此方法传入经纬度信息
 @param location CLLocation *型的地理信息
 */
+ (void)setLocation:(CLLocation *)location;



@end
