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
 This class uses a NOAPI property behind the scenes to communicate with a NetworkObjects server and cache them to a NSManagedObjectContext. It returns NSManagedObject instances that conform to NOResourceProtocol.
 */

@interface NOAPICachedStore : NOAPI
{
    /** Hierarchy of dictionaries with dates a resource with a particular resource ID was cached. */
    NSDictionary *_dateCached;
    
    /** Dictionary of NSOperationQueue for accessing a sub dictionary in @c _dateCached */
    NSDictionary *_dateCachedOperationQueues;
}

// must initialize the persistent store coordinator

/**
 Upon initialization, a @c NSManagedObjectContext is initialized without a persistent store coordinator. In order for this class to function properly assign a @c NSPersistentStoreCoordinator to this property. When initializng the @c NSPersistentStoreCoordinator make sure to use the same @c NSManagedObjectModel instance specified in @c self.model
 
 @see NSManagedObjectContext
 
 */

#pragma mark - Cache

@property (readonly) NSManagedObjectContext *context;

/** Returns the date when this Resource was cached (either downloaded or created) */

-(NSDate *)dateCachedForResource:(NSString *)resourceName
                      resourceID:(NSUInteger)resourceID;

#pragma mark - Requests

/** Performs a fetch request on the server and returns the results in the completion block. The fetch request results are filtered by the permissions the session has.
 
 @param resourceName Name of the entity that will be searched.
 
 @param parameters Dictionary with Core Data compatible values. This dictionary should use @c NOSearchParameter values for valid keys.
 
 @param urlSession The URL session that will be used to create the data task. If this parameter is nil than the default URL session is used.
 
 @param completionBlock The completion block that will be called when a response is recieved from the server. If an error occurred then the completion block's @c error argument will be set to an @c NSError instance. If there is no error then the completion block's @c results argument will be set to an array of cached resource instances. Note that performing a search does not update the cached results' data which must be retrieved separately.
 
 @return The data task that is communicating with the server. The data task returned is already resumed.
 
 @see NOSearchParameter
 
 */

-(NSURLSessionDataTask *)searchForCachedResource:(NSString *)resourceName
                                  withParameters:(NSDictionary *)parameters
                                      URLSession:(NSURLSession *)urlSession
                                      completion:(void (^)(NSError *error, NSArray *results))completionBlock;

-(NSURLSessionDataTask *)getCachedResource:(NSString *)resourceName
                                resourceID:(NSUInteger)resourceID
                                URLSession:(NSURLSession *)urlSession
                                completion:(void (^)(NSError *error, NSManagedObject<NOResourceKeysProtocol> *resource))completionBlock;

-(NSURLSessionDataTask *)editCachedResource:(NSManagedObject<NOResourceKeysProtocol>*)resource
                                    changes:(NSDictionary *)values
                                 URLSession:(NSURLSession *)urlSession
                                 completion:(void (^)(NSError *error))completionBlock;

-(NSURLSessionDataTask *)deleteCachedResource:(NSManagedObject<NOResourceKeysProtocol>*)resource
                                   URLSession:(NSURLSession *)urlSession
                                   completion:(void (^)(NSError *error))completionBlock;

-(NSURLSessionDataTask *)createCachedResource:(NSString *)resourceName
                          initialValues:(NSDictionary *)initialValues
                             URLSession:(NSURLSession *)urlSession
                             completion:(void (^)(NSError *error, NSManagedObject<NOResourceKeysProtocol> *resource)) completionBlock;

-(NSURLSessionDataTask *)performFunction:(NSString *)functionName
                        onCachedResource:(NSManagedObject<NOResourceKeysProtocol>*)resource
                          withJSONObject:(NSDictionary *)jsonObject
                              URLSession:(NSURLSession *)urlSession
                              completion:(void (^)(NSError *error, NSNumber *statusCode, NSDictionary *jsonResponse))completionBlock;

@end
