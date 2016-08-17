//
//  InAppRageIAPHelper.cpp
//  MagicTower
//
//  Created by xcode31 on 16/3/3.
//
//

#import "InAppRageIAPHelper.h"

@implementation InAppRageIAPHelper

static InAppRageIAPHelper * _sharedHelper;

+ (InAppRageIAPHelper *) sharedHelper {
    
    if (_sharedHelper != nil) {
        return _sharedHelper;
    }
    _sharedHelper = [[InAppRageIAPHelper alloc] init];
    return _sharedHelper;
    
}

- (id)init {
    
    NSArray *productIdentifiers = @[
                                    @"com.cdbandou.fang_buy1",
                                    @"com.cdbandou.fang_buy2",
                                    ];
    
    if ((self = [super initWithProductIdentifiers:productIdentifiers])) {
        
    }
    return self;
    
}

@end
