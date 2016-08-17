//
//  GameCenterTools.hpp
//  MagicTower
//
//  Created by xcode31 on 16/3/2.
//
//

#ifndef GameCenterTools_hpp
#define GameCenterTools_hpp

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <GameKit/GameKit.h>

@interface GameCenterTools : NSObject <GKLeaderboardViewControllerDelegate, GKAchievementViewControllerDelegate, GKMatchmakerViewControllerDelegate, GKMatchDelegate> {
    BOOL gameCenterAvailable;
    BOOL userAuthenticated;
    
};
@property (assign, readonly) BOOL gameCenterAvailable;
@property float gamePercent;

+ (GameCenterTools *)sharedGameKitHelper;
- (void) authenticateLocalUser;

- (void) showLeaderboard;
- (void)leaderboardViewControllerDidFinish:(GKLeaderboardViewController *)viewController;
- (void) reportScore: (int64_t) score forCategory: (NSString*) category;
- (void) retrieveTopTenScores;
- (float) getPercentOfPaihang;
@end

#endif /* GameCenterTools_hpp */
