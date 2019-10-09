//  Copyright (c) 2018 Rollbar, Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "JSONModelLib.h"
#import "RollbarLevel.h"

typedef NS_ENUM(NSUInteger, CaptureIpType) {
    CaptureIpFull,
    CaptureIpAnonymize,
    CaptureIpNone
};

@interface RollbarConfiguration : JSONModel

+ (RollbarConfiguration*)configuration;

- (id)initWithLoadedConfiguration;

- (void)_setRoot;
- (void)save;

- (void)setReportingRate:(NSUInteger)maximumReportsPerMinute;
- (void)setRollbarLevel:(RollbarLevel)level;
- (RollbarLevel)getRollbarLevel;

- (void)setPersonId:(NSString*)personId username:(NSString*)username email:(NSString*)email;
- (void)setServerHost:(NSString *)host root:(NSString*)root branch:(NSString*)branch codeVersion:(NSString*)codeVersion;
- (void)setNotifierName:(NSString *)name version:(NSString *)version;
- (void)setCodeFramework:(NSString *)framework;
- (void)setCodeVersion:(NSString *)codeVersion;

- (void)setPayloadModificationBlock:(void (^)(NSMutableDictionary*))payloadModificationBlock;
- (void)setCheckIgnoreBlock:(BOOL (^)(NSDictionary*))checkIgnoreBlock;

- (void)addScrubField:(NSString *)field;
- (void)removeScrubField:(NSString *)field;
- (void)addScrubWhitelistField:(NSString *)field;
- (void)removeScrubWhitelistField:(NSString *)field;

- (void)addTelemetryViewInputToScrub:(NSString *)input;
- (void)removeTelemetryViewInputToScrub:(NSString *)input;

- (void)setRequestId:(NSString*)requestId;
- (void)setCaptureIpType:(CaptureIpType)captureIp;

- (void)setMaximumTelemetryData:(NSInteger)maximumTelemetryData;
- (void)setCaptureLogAsTelemetryData:(BOOL)captureLog;
- (void)setCaptureConnectivityAsTelemetryData:(BOOL)captureConnectivity;

- (NSDictionary *)customData;

// Developer options:
@property (nonatomic) BOOL enabled;
@property (nonatomic) BOOL transmit;
@property (nonatomic) BOOL logPayload;
@property (readonly, nonatomic, copy) NSString *logPayloadFile;

// Rollbar project endpoint/destination:
@property (nonatomic, copy) NSString *accessToken;
@property (nonatomic, copy) NSString *environment;
@property (nonatomic, copy) NSString *endpoint;

// HTTP proxy:
@property (nonatomic) BOOL httpProxyEnabled;
@property (nonatomic, copy) NSString *httpProxy;
@property (nonatomic) NSNumber *httpProxyPort;

// HTTPS proxy:
@property (nonatomic) BOOL httpsProxyEnabled;
@property (nonatomic, copy) NSString *httpsProxy;
@property (nonatomic) NSNumber *httpsProxyPort;

// Logging options:
@property (nonatomic, copy) NSString *crashLevel;
@property (nonatomic, copy) NSString *logLevel;
@property (readonly, nonatomic) NSUInteger maximumReportsPerMinute;
@property (readonly, nonatomic) BOOL shouldCaptureConnectivity;

// Payload content related:
// ========================
// Decides whether or not to send payload. Returns true to ignore, false to send
@property (readonly, nonatomic, copy) BOOL (^checkIgnore)(NSDictionary *payload);
// Modify payload
@property (readonly, nonatomic, copy) void (^payloadModification)(NSMutableDictionary *payload);
// Fields to scrub from the payload
@property (readonly, nonatomic, strong) NSMutableSet *scrubFields;
// Fields to not scrub from the payload even if they mention among scrubFields:
@property (readonly, nonatomic, strong) NSMutableSet *scrubWhitelistFields;
@property (readonly, nonatomic) CaptureIpType captureIp;

// Telemetry:
@property (nonatomic) BOOL telemetryEnabled;
@property (nonatomic) BOOL scrubViewInputsTelemetry;
@property (nonatomic, strong) NSMutableSet *telemetryViewInputsToScrub;

@property (readonly, nonatomic, copy) NSString *codeVersion;

@property (readonly, nonatomic, copy) NSString *serverHost;
@property (readonly, nonatomic, copy) NSString *serverRoot;
@property (readonly, nonatomic, copy) NSString *serverBranch;
@property (readonly, nonatomic, copy) NSString *serverCodeVersion;

@property (readonly, nonatomic, copy) NSString *notifierName;
@property (readonly, nonatomic, copy) NSString *notifierVersion;
@property (readonly, nonatomic, copy) NSString *framework;

// Person/user tracking:
@property (readonly, nonatomic, copy) NSString *personId;
@property (readonly, nonatomic, copy) NSString *personUsername;
@property (readonly, nonatomic, copy) NSString *personEmail;

// ID to link request between client/server
@property (readonly, nonatomic, copy) NSString *requestId;

@end
