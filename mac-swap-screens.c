/* 
 * Swap to identical screens on a mac
 * 
 * Taken from Stackoverflow
 * https://stackoverflow.com/questions/53370613/change-macos-display-arrangement-through-command-line-applescript
 */

#include <IOKit/graphics/IOGraphicsLib.h>
#include <ApplicationServices/ApplicationServices.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h>

int main(int argc, const char * argv[]) {
    const UInt32 MaxDisplays = 10;
    UInt32 displayCount = 0;

    CGDirectDisplayID screenList[MaxDisplays];
    CGGetOnlineDisplayList(MaxDisplays, screenList, &displayCount);

    printf("      ID    Model   Serial     Unit   Vendor    Origin      Size A M O\n");
    for(UInt32 i=0; i<displayCount; ++i) {
        UInt32 modelNumber = CGDisplayModelNumber(screenList[i]);
        CGRect bounds = CGDisplayBounds(screenList[i]);
        UInt32 serialNumber = CGDisplaySerialNumber(screenList[i]);
        UInt32 unitNumber = CGDisplayUnitNumber(screenList[i]);
        UInt32 vendorNumber = CGDisplayVendorNumber(screenList[i]);
        boolean_t isActive = CGDisplayIsActive(screenList[i]);
        boolean_t isMain = CGDisplayIsMain(screenList[i]);
        boolean_t isOnline = CGDisplayIsOnline(screenList[i]);

        printf("%8x %8x %8x %8x %8x %04ux%04u %04ux%04u %c %c %c\n", 
            screenList[i],
            modelNumber, 
            serialNumber, 
            unitNumber, 
            vendorNumber, 
            (UInt32)bounds.origin.x, 
            (UInt32)bounds.origin.y,
            (UInt32)bounds.size.width, 
            (UInt32)bounds.size.height,
            isActive ? 'y' : ' ',
            isMain ? 'y' : ' ',
            isOnline ? 'y' : ' ');
    }

    if (displayCount == 2) {
        CGDisplayConfigRef configRef;
        CGBeginDisplayConfiguration(&configRef);

        CGConfigureDisplayOrigin(configRef, screenList[0], CGDisplayBounds(screenList[1]).origin.x, CGDisplayBounds(screenList[1]).origin.y);
        CGConfigureDisplayOrigin(configRef, screenList[1], CGDisplayBounds(screenList[0]).origin.x, CGDisplayBounds(screenList[0]).origin.y);
        
        CGCompleteDisplayConfiguration(configRef, kCGConfigurePermanently);

        return 0;
    } else {
        fprintf(stderr, "There are %u screens: do not know which ones to swap", displayCount);

        return 1;
    }
}