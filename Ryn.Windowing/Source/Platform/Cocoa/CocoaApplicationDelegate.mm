#include "CocoaApplicationDelegate.hh"

@implementation CocoaApplicationDelegate

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)sender
{
    return YES;
}

- (void)applicationDidFinishLaunching:(NSNotification*)notification
{
    NSEvent* event = [NSEvent otherEventWithType:NSEventTypeApplicationDefined
        location:NSMakePoint(0, 0)
        modifierFlags:0
        timestamp:0
        windowNumber:0
        context:nil
        subtype:0
        data1:0
        data2:0];

    [NSApp postEvent:event atStart:YES];
    [NSApp stop:nil];
}

@end
