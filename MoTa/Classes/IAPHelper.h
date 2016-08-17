//
//  IAPHelper.hpp
//  MagicTower
//
//  Created by xcode31 on 16/3/3.
//
//

#ifndef IAPHelper_hpp
#define IAPHelper_hpp

#import <Foundation/Foundation.h>
#import "StoreKit/StoreKit.h"

#define kProductsLoadedNotification         @"ProductsLoaded"
#define kProductPurchasedNotification       @"ProductPurchased"
#define kProductPurchaseFailedNotification  @"ProductPurchaseFailed"

@interface IAPHelper : NSObject <SKProductsRequestDelegate, SKPaymentTransactionObserver> {
    NSArray * _productIdentifiers;
    NSArray * _products;
    NSMutableSet * _purchasedProducts;
    SKProductsRequest * _request;
    
    UIAlertView * co_alert;
}

@property (retain) NSArray *productIdentifiers;
@property (retain) NSArray * products;
@property (retain) NSMutableSet *purchasedProducts;
@property (retain) SKProductsRequest *request;

- (void)requestRestore;
- (void)requestProducts;
- (id)initWithProductIdentifiers:(NSArray *)productIdentifiers;
- (void)buyProductIdentifier:(NSString *)productIdentifier;

@end

#endif /* IAPHelper_hpp */
