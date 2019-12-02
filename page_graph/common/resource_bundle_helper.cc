/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/common/resource_bundle_helper.h"

#include "base/command_line.h"
#include "base/path_service.h"
#include "components/nacl/common/nacl_switches.h"
#include "content/public/common/content_switches.h"
#include "services/service_manager/embedder/switches.h"
#include "ui/base/resource/resource_bundle.h"

#if defined(OS_MACOSX)
#include "base/mac/foundation_util.h"
#include "base/strings/sys_string_conversions.h"
#endif

namespace {

base::FilePath GetResourcesPakFilePath() {
#if defined(OS_MACOSX)
  return base::mac::PathForFrameworkBundleResource(
      CFSTR("brave_resources.pak"));
#else
  base::FilePath pak_path;
  base::PathService::Get(base::DIR_MODULE, &pak_path);
  pak_path = pak_path.AppendASCII("brave_resources.pak");
  return pak_path;
#endif  // OS_MACOSX
}

base::FilePath GetScaledResourcesPakFilePath(ui::ScaleFactor scale_factor) {
  DCHECK(scale_factor == ui::SCALE_FACTOR_100P ||
         scale_factor == ui::SCALE_FACTOR_200P);

  const char* pak_file =
      (scale_factor == ui::SCALE_FACTOR_100P) ? "brave_100_percent.pak"
                                              : "brave_200_percent.pak";
#if defined(OS_MACOSX)
  base::ScopedCFTypeRef<CFStringRef> pak_file_mac(
      base::SysUTF8ToCFStringRef(pak_file));
  return base::mac::PathForFrameworkBundleResource(pak_file_mac);
#else
  base::FilePath pak_path;
  base::PathService::Get(base::DIR_MODULE, &pak_path);
  pak_path = pak_path.AppendASCII(pak_file);
  return pak_path;
#endif  // OS_MACOSX
}

}

namespace brave {

void InitializeResourceBundle() {
  auto& rb = ui::ResourceBundle::GetSharedInstance();
  rb.AddDataPackFromPath(GetResourcesPakFilePath(), ui::SCALE_FACTOR_NONE);

  rb.AddDataPackFromPath(GetScaledResourcesPakFilePath(ui::SCALE_FACTOR_100P),
                         ui::SCALE_FACTOR_100P);

  if (ui::ResourceBundle::IsScaleFactorSupported(ui::SCALE_FACTOR_200P)) {
    rb.AddDataPackFromPath(GetScaledResourcesPakFilePath(ui::SCALE_FACTOR_200P),
                           ui::SCALE_FACTOR_200P);
  }
}

// Returns true if this subprocess type needs the ResourceBundle initialized
// and resources loaded.
bool SubprocessNeedsResourceBundle() {
  auto cmd = *base::CommandLine::ForCurrentProcess();
  std::string process_type = cmd.GetSwitchValueASCII(switches::kProcessType);
  return
#if defined(OS_POSIX) && !defined(OS_MACOSX)
      // The zygote process opens the resources for the renderers.
      process_type == service_manager::switches::kZygoteProcess ||
#endif
#if defined(OS_MACOSX)
      // Mac needs them too for scrollbar related images and for sandbox
      // profiles.
#if !defined(DISABLE_NACL)
      process_type == switches::kNaClLoaderProcess ||
#endif
      process_type == switches::kPpapiPluginProcess ||
      process_type == switches::kPpapiBrokerProcess ||
      process_type == switches::kGpuProcess ||
#endif
      process_type == switches::kRendererProcess ||
      process_type == switches::kUtilityProcess;
}

}
