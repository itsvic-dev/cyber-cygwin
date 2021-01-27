pragma Singleton

import QtQuick 2.4
import QtQuick.Window 2.2

QtObject {
    id: units

	readonly property double rowHeight: iconSizes.large * 0.95
	readonly property double rowHeightAlt: rowHeight * 0.8

    /**
     * The fundamental unit of space that should be used for sizes, expressed in pixels.
     * Given the screen has an accurate DPI settings, it corresponds to the height of
     * the font's boundingRect.
     */
    property int gridUnit: fontMetrics.height

    /**
     * units.iconSizes provides access to platform-dependent icon sizing
     *
     * The icon sizes provided are normalized for different DPI, so icons
     * will scale depending on the DPI.
     *
     * Icon sizes from KIconLoader, adjusted to devicePixelRatio:
     * * small
     * * smallMedium
     * * medium
     * * large
     * * huge
     * * enormous
     *
     * Not devicePixelRation-adjusted::
     * * desktop
     */
    property QtObject iconSizes: QtObject {
        property int small: Math.floor(fontMetrics.roundedIconSize(16 * devicePixelRatio) * 1)
        property int smallMedium: Math.floor(fontMetrics.roundedIconSize(22 * devicePixelRatio) * 1)
        property int medium: Math.floor(fontMetrics.roundedIconSize(32 * devicePixelRatio) * 1)
        property int large: Math.floor(fontMetrics.roundedIconSize(48 * devicePixelRatio) * 1)
        property int huge: Math.floor(fontMetrics.roundedIconSize(64 * devicePixelRatio) * 1)
        property int enormous: Math.floor(128 * devicePixelRatio * 1)
    }

    /**
     * units.smallSpacing is the amount of spacing that should be used around smaller UI elements,
     * for example as spacing in Columns. Internally, this size depends on the size of
     * the default font as rendered on the screen, so it takes user-configured font size and DPI
     * into account.
     */
    property int smallSpacing: Math.floor(gridUnit / 4)

    /**
     * units.largeSpacing is the amount of spacing that should be used inside bigger UI elements,
     * for example between an icon and the corresponding text. Internally, this size depends on
     * the size of the default font as rendered on the screen, so it takes user-configured font
     * size and DPI into account.
     */
    property int largeSpacing: smallSpacing * 2

    /**
     * The ratio between physical and device-independent pixels. This value does not depend on the \
     * size of the configured font. If you want to take font sizes into account when scaling elements,
     * use theme.mSize(theme.defaultFont), units.smallSpacing and units.largeSpacing.
     * The devicePixelRatio follows the definition of "device independent pixel" by Microsoft.
     */
    property real devicePixelRatio: Math.max(1, ((fontMetrics.font.pixelSize * 0.75) / fontMetrics.font.pointSize))

    /**
     * metrics used by the default font
     */
    property variant fontMetrics: FontMetrics {
        function roundedIconSize(size) {
            if (size < 16) {
                return size;
            } else if (size < 22) {
                return 16;
            } else if (size < 32) {
                return 22;
            } else if (size < 48) {
                return 32;
            } else if (size < 64) {
                return 48;
            } else {
                return size;
            }
        }
    }
}