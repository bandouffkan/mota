//
//  IAPHelper.cpp
//  MagicTower
//
//  Created by xcode31 on 16/3/3.
//
//

#import "IAPHelper.h"
#include "cocos2d.h"
#include "ShopFace.hpp"

using namespace cocos2d;

@implementation IAPHelper
@synthesize productIdentifiers = _productIdentifiers;
@synthesize products = _products;
@synthesize purchasedProducts = _purchasedProducts;
@synthesize request = _request;

- (id)initWithProductIdentifiers:(NSArray *)productIdentifiers {
    if ((self = [super init])) {
        
        // Store product identifiers
        _productIdentifiers = [productIdentifiers retain];
        
        // Check for previously purchased products
        NSMutableSet * purchasedProducts = [NSMutableSet set];
        for (NSString * productIdentifier in _productIdentifiers) {
            BOOL productPurchased = [[NSUserDefaults standardUserDefaults] boolForKey:productIdentifier];
            if (productPurchased) {
                [purchasedProducts addObject:productIdentifier];
                NSLog(@"Previously purchased: %@", productIdentifier);
            }
            NSLog(@"Not purchased: %@", productIdentifier);
        }
        self.purchasedProducts = purchasedProducts;
        
    }
    return self;
}

- (void)requestProducts {
    
    self.request = [[[SKProductsRequest alloc] initWithProductIdentifiers:[NSSet setWithArray:_productIdentifiers]] autorelease];
    _request.delegate = self;
    [_request start];
    
}

- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response {
    
    NSLog(@"Received products results...");
    self.products = response.products;
    self.request = nil;
    
    [[NSNotificationCenter defaultCenter] postNotificationName:kProductsLoadedNotification object:_products];
}

-(void)requestRestore
{
    
    [[SKPaymentQueue defaultQueue] restoreCompletedTransactions];
    
    
    co_alert = [[UIAlertView alloc] initWithTitle:@"Connecting..."
                                          message:nil
                                         delegate:nil
                                cancelButtonTitle:nil otherButtonTitles:nil];
    [co_alert show];
    [co_alert release];
    
    UIActivityIndicatorView *aiv = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleGray];
    [aiv startAnimating];
    [co_alert setValue:aiv forKey:@"accessoryView"];
    [aiv release];
    
}


-(void) paymentQueue:(SKPaymentQueue *) paymentQueue restoreCompletedTransactionsFailedWithError:(NSError *)error{
    NSLog(@"-------paymentQueue-- restoreCompletedTransactionsFailedWithError--");
    
    
    [co_alert dismissWithClickedButtonIndex:0 animated:YES];
    
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Restore Failed!"
                                                    message:error.localizedDescription
                                                   delegate:nil
                                          cancelButtonTitle:@"Ok" otherButtonTitles:nil];
    [alert show];
    [alert release];
    
}

- (void)paymentQueueRestoreCompletedTransactionsFinished:(SKPaymentQueue *)queue {
    [co_alert dismissWithClickedButtonIndex:0 animated:YES];
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Restore Success!"
                                                    message:nil
                                                   delegate:nil
                                          cancelButtonTitle:@"Ok" otherButtonTitles:nil];
    [alert show];
    [alert release];
}

- (void)recordTransaction:(SKPaymentTransaction *)transaction {
    // TODO: Record the transaction on the server side...
}

- (void)provideContent:(NSString *)productIdentifier {
    
    NSLog(@"Toggling flag for: %@", productIdentifier);
    [[NSUserDefaults standardUserDefaults] setBool:TRUE forKey:productIdentifier];
    [[NSUserDefaults standardUserDefaults] synchronize];
    [_purchasedProducts addObject:productIdentifier];
    
    [[NSNotificationCenter defaultCenter] postNotificationName:kProductPurchasedNotification object:productIdentifier];
    
}

- (void)completeTransaction:(SKPaymentTransaction *)transaction {
    
    NSLog(@"completeTransaction...");
    
    [self recordTransaction: transaction];
    [self provideContent: transaction.payment.productIdentifier];
    [[SKPaymentQueue defaultQueue] finishTransaction: transaction];
    ShopFace::isResulted = true;
    ShopFace::buyResults =  2;
}

- (void)restoreTransaction:(SKPaymentTransaction *)transaction {
    
    NSLog(@"restoreTransaction...");
    
    [self recordTransaction: transaction];
    [self provideContent: transaction.originalTransaction.payment.productIdentifier];
    [[SKPaymentQueue defaultQueue] finishTransaction: transaction];
    ShopFace::isResulted = true;
    ShopFace::buyResults =  1;
}

- (void)failedTransaction:(SKPaymentTransaction *)transaction {
    
    if (transaction.error.code != SKErrorPaymentCancelled)
    {
        NSLog(@"Transaction error: %@", transaction.error.localizedDescription);
    }
    
    [[NSNotificationCenter defaultCenter] postNotificationName:kProductPurchaseFailedNotification object:transaction];
    
    [[SKPaymentQueue defaultQueue] finishTransaction: transaction];
    ShopFace::isResulted = true;
    ShopFace::buyResults =  0;
}

- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions
{
    for (SKPaymentTransaction *transaction in transactions)
    {
        switch (transaction.transactionState)
        {
            case SKPaymentTransactionStatePurchased:
                [self completeTransaction:transaction];
                break;
            case SKPaymentTransactionStateFailed:
                [self failedTransaction:transaction];
                break;
            case SKPaymentTransactionStateRestored:
                [self restoreTransaction:transaction];
            default:
                break;
        }
        
        switch (transaction.transactionState)
        {
            case SKPaymentTransactionStatePurchased:
            case SKPaymentTransactionStateFailed:
            case SKPaymentTransactionStateRestored:
                [co_alert dismissWithClickedButtonIndex:0 animated:YES];
            default:
                break;
        }
    }
    
}

- (void)buyProductIdentifier:(NSString *)productIdentifier {
    
    NSLog(@"Buying %@...", productIdentifier);
    
    SKPayment *payment = [SKPayment paymentWithProductIdentifier:productIdentifier];
    [[SKPaymentQueue defaultQueue] addPayment:payment];
    
    co_alert = [[UIAlertView alloc] initWithTitle:@"Connecting..."
                                          message:nil
                                         delegate:nil
                                cancelButtonTitle:nil otherButtonTitles:nil];
    [co_alert show];
    
    UIActivityIndicatorView *aiv = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleGray];
    [aiv startAnimating];
    [co_alert setValue:aiv forKey:@"accessoryView"];
    [aiv release];
}

- (void)dealloc
{
    [_productIdentifiers release];
    _productIdentifiers = nil;
    [_products release];
    _products = nil;
    [_purchasedProducts release];
    _purchasedProducts = nil;
    [_request release];
    _request = nil;
    [super dealloc];
}

@end

