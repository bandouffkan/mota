//
//  GameCenterTools.cpp
//  MagicTower
//
//  Created by xcode31 on 16/3/2.
//
//

#import "GameCenterTools.h"
#import <Social/Social.h>
#import <ACCOUNTS/ACAccount.h>

@implementation GameCenterTools

@synthesize gameCenterAvailable;
@synthesize gamePercent;

static GameCenterTools *sharedHelper = nil;
static UIViewController* currentModalViewController = nil;
+ (GameCenterTools *) sharedGameKitHelper {
    if (!sharedHelper) {
        sharedHelper = [[GameCenterTools alloc] init];
    }
    return sharedHelper;
}
//用于验证
- (BOOL)isGameCenterAvailable {
    // check for presence of GKLocalPlayer API
    Class gcClass = (NSClassFromString(@"GKLocalPlayer"));
    
    // check if the device is running iOS 4.1 or later
    NSString *reqSysVer =@"6.0";
    NSString *currSysVer = [[UIDevice currentDevice] systemVersion];
    BOOL osVersionSupported = ([currSysVer compare:reqSysVer
                                           options:NSNumericSearch] != NSOrderedAscending);
    
    return (gcClass && osVersionSupported);
}
- (id)init {
    if ((self = [super init])) {
        gameCenterAvailable = [self isGameCenterAvailable];
        if (gameCenterAvailable) {
            NSNotificationCenter *nc =
            [NSNotificationCenter defaultCenter];
            [nc addObserver:self
                   selector:@selector(authenticationChanged)
                       name:GKPlayerAuthenticationDidChangeNotificationName
                     object:nil];
        }
    }
    return self;
}
//后台回调登陆验证
- (void)authenticationChanged {
    gamePercent = -1;
    if ([GKLocalPlayer localPlayer].isAuthenticated &&!userAuthenticated) {
        NSLog(@"Authentication changed: player authenticated.");
        userAuthenticated = TRUE;
    } else if (![GKLocalPlayer localPlayer].isAuthenticated && userAuthenticated) {
        NSLog(@"Authentication changed: player not authenticated");
        userAuthenticated = FALSE;
    }
    //740912609@qq.com
    //
    
}
//调用gamecenter登录
- (void)authenticateLocalUser {
    
    if (!gameCenterAvailable) return;
    gamePercent = -1;
    NSLog(@"Authenticating local user...");
    if ([GKLocalPlayer localPlayer].authenticated == NO) {
        [[GKLocalPlayer localPlayer] authenticateWithCompletionHandler:nil];
    } else {
        NSLog(@"Already authenticated!");
    }
}
//显示排行榜
- (void) showLeaderboard
{
    if (!gameCenterAvailable) return;
    
    GKLeaderboardViewController *leaderboardController = [[GKLeaderboardViewController alloc] init];
    if (leaderboardController != nil) {
        leaderboardController.leaderboardDelegate = self;
        
        UIWindow *window = [[UIApplication sharedApplication] keyWindow];
        currentModalViewController = [[UIViewController alloc] init];
        [window addSubview:currentModalViewController.view];
        [currentModalViewController presentModalViewController:leaderboardController animated:YES];
        
    }
    
}
//关闭排行榜回调
- (void)leaderboardViewControllerDidFinish:(GKLeaderboardViewController *)viewController{
    if(currentModalViewController !=nil){
        [currentModalViewController dismissModalViewControllerAnimated:NO];
        [currentModalViewController release];
        [currentModalViewController.view removeFromSuperview];
        currentModalViewController = nil;
    }
}
// 上传一个分数
- (void) reportScore: (int64_t) score forCategory: (NSString*) category
{
    GKScore *scoreReporter = [[[GKScore alloc] initWithCategory:category] autorelease];
    scoreReporter.value = score;
    [scoreReporter reportScoreWithCompletionHandler:^(NSError *error) {
        if (error != nil)
        {
            // handle the reporting error
            NSLog(@"上传分数出错.");
            gamePercent = -1;
            //If your application receives a network error, you should not discard the score.
            //Instead, store the score object and attempt to report the player’s process at
            //a later time.
        }else {
            NSLog(@"上传分数成功:%lld", score);
            //            scoreReporter.rank;
            
        }
        
    }];
}

- (void) retrieveTopTenScores
{
    GKLeaderboard *leaderboardRequest = [[GKLeaderboard alloc] init];
    if (leaderboardRequest != nil)
    {
        leaderboardRequest.playerScope = GKLeaderboardPlayerScopeGlobal;
        leaderboardRequest.timeScope = GKLeaderboardTimeScopeAllTime;
        leaderboardRequest.range = NSMakeRange(1,10);
        leaderboardRequest.category = @"com.cdbandou.fang_top";
        [leaderboardRequest loadScoresWithCompletionHandler: ^(NSArray *scores, NSError *error) {
            if (error != nil){
                // handle the error.
                NSLog(@"下载失败");
            }
            if (scores != nil){
                // process the score information.
                
                NSLog(@"下载成功.....: %lu.",(unsigned long)leaderboardRequest.maxRange);
                GKScore* localScore = leaderboardRequest.localPlayerScore;
                
                gamePercent = (float)localScore.rank / (float)leaderboardRequest.maxRange;
                NSLog(@"下载成功.....: %f.",gamePercent);
                
                NSArray *tempScore = [NSArray arrayWithArray:leaderboardRequest.scores];
                for (GKScore *obj in tempScore) {
                    NSLog(@"    playerID            : %@",obj.playerID);
                    NSLog(@"    category            : %@",obj.category);
                    NSLog(@"    date                : %@",obj.date);
                    NSLog(@"    formattedValue    : %@",obj.formattedValue);
                    NSLog(@"    value                : %d",(int)obj.value);
                    NSLog(@"    rank                : %ld",(long)obj.rank);
                    NSLog(@"**************************************");
                }
            }
        }];
    }
    
}

- (float) getPercentOfPaihang
{
    NSLog(@"game percent............: %f.",gamePercent);
    return (int)(gamePercent * 100);
}


@end
