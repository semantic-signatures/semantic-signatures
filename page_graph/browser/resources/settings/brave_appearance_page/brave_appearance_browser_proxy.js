/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

cr.define('settings', function() {
  /** @interface */
  class BraveAppearanceBrowserProxy {
    /**
     * @return {!Promise<string>}
     */
    getBraveThemeList() {}
  }

  /**
   * @implements {settings.BraveAppearanceBrowserProxy}
   */
  class BraveAppearanceBrowserProxyImpl {
    /** @override */
    getBraveThemeList() {
      return new Promise(resolve => chrome.braveTheme.getBraveThemeList(resolve))
    }
  }

  cr.addSingletonGetter(BraveAppearanceBrowserProxyImpl);

  return {
    BraveAppearanceBrowserProxy: BraveAppearanceBrowserProxy,
    BraveAppearanceBrowserProxyImpl: BraveAppearanceBrowserProxyImpl,
  };
});
