package net.janrupf.ujr.core.platform.abstraction;

import net.janrupf.ujr.api.config.UlConfig;
import net.janrupf.ujr.api.filesystem.UltralightFilesystem;
import net.janrupf.ujr.api.logger.UltralightLogger;

public interface UlPlatform {
    void setConfig(UlConfig config);

    void usePlatformFontLoader();

    void setLogger(UltralightLogger logger);

    UltralightLogger getLogger();

    void setFilesystem(UltralightFilesystem filesystem);

    UltralightFilesystem getFilesystem();
}
