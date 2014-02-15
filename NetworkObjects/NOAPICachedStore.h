//
//  NOAPICachedStore.h
//  NetworkObjects
//
//  Created by Alsey Coleman Miller on 11/16/13.
//  Copyright (c) 2013 CDA. All rights reserved.
//

@import Foundation;
@import CoreData;
#import <NetworkObjects/NOAPI.h>
#import <NetworkObjects/NOResourceProtocol.h>

/**
 This class uses a NOAPI property behind the scenes to communicate with a NetworkObjects server and cache them to a Core Data context. It returns NSManagedObject instances that conform to NOResourceProtocol.
 */

@interface NOAPICachedStore : NSObject

/**
 This property must be set to a non-nil value and be properly set up in order for this class to function correctly. 
 
 @see NOAPI
 */

@property NOAPI *api;

// must initialize the persistent store coordinator

/**
 This property must be set to a non-nil value and be properly set up in order for this class to function correctly.
 
 */

@property (readonly) NSManagedObjectContext *context;

#pragma mark - Requests

-(NSURLSessionDataTask *)getResource:(NSString *)resourceName
                          resourceID:(NSUInteger)resourceID
                          completion:(void (^)(NSError *error, NSManagedObject<NOResourceKeysProtocol> *resource))completionBlock;

-(NSURLSessionDataTask *)editResource:(NSManagedObject<NOResourceKeysProtocol>*)resource
                              changes:(NSDictionary *)values
                           completion:(void (^)(NSError *error))completionBlock;

-(NSURLSessionDataTask *)deleteResource:(NSManagedObject<NOResourceKeysProtocol>*)resource
                             completion:(void (^)(NSError *error))completionBlock;

-(NSURLSessionDataTask *)createResource:(NSString *)resourceName
                          initialValues:(NSDictionary *)initialValues
                             completion:(void (^)(NSError *error, NSManagedObject<NOResourceKeysProtocol> *resource)) completionBlock;

-(NSURLSessionDataTask *)performFunction:(NSString *)functionName
                              onResource:(NSManagedObject<NOResourceKeysProtocol>*)resource
                          withJSONObject:(NSDictionary *)jsonObject
                              completion:(void (^)(NSError *error, NSNumber *statusCode, NSDictionary *jsonResponse))completionBlock;

@end
