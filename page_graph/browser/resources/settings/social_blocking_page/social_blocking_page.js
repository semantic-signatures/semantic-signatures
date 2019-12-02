/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

(function() {
'use strict';

/**
 * 'settings-social-blocking-page' is the settings page containing brave's
 * social blocking options
 */
Polymer({
  is: 'settings-social-blocking-page',

  properties: {},

  /** @private {?settings.DefaultBraveShieldsBrowserProxy} */
  browserProxy_: null,

  /** @override */
  created: function() {
    this.browserProxy_ = settings.SocialBlockingBrowserProxyImpl.getInstance();
  },

  /** @override */
  ready: function() {},
});
})();
