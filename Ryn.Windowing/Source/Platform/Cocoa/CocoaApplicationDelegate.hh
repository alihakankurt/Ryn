#pragma once

#import <Cocoa/Cocoa.h>

@interface CocoaApplicationDelegate : NSObject <NSApplicationDelegate>

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)sender;
- (void)applicationDidFinishLaunching:(NSNotification*)notification;

@end
