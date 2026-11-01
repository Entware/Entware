---
name: entware-package-update
description: Update existing packages in Entware/OpenWrt feeds to current upstream releases, including version discovery, source hashes, patch refresh, cross-compilation, package inspection, and final diffs. Use for package-version maintenance in an Entware build tree; do not use for adding unrelated new packages.
---

# Entware Package Update

Work in the existing Entware tree.

## Repository constraints

- Never run the build as root.
- Use `make -j16` for normal builds. For diagnostics, use the exact failing target with one job and verbose output.
- Do not edit generated files under `build_dir`, `staging_dir`, or `tmp`.
- Before changing a package, inspect its `Makefile`, patches, files, current git diff, and relevant git history.
- After a fix, rebuild the affected package before starting any full build.

## Select an update

1. Inspect the feed package list, each relevant `Makefile`, its patches/files, repository status, and the package's git history before editing.
2. Treat Makefile comments about the last usable release, compiler/kernel/libc/CMake requirements, abandoned upstreams, or compatibility constraints as authoritative until verified otherwise.
3. Check releases directly at authoritative upstream sources. Do not use Repology for Entware version status. Prefer stable releases and record the exact tag or revision.
4. When asked for the first updateable package, preserve the feed's requested ordering and skip packages that are abandoned, already current, or explicitly pinned by compatibility comments.

For Go packages, read the `go` directive from the candidate release's authoritative `go.mod` and compare it with the staged host compiler (`staging_dir/host/bin/go version`). Do not reject a release based only on the old packaged compiler version when a toolchain update is also in scope. Filter out nightly, prerelease, release-candidate, and similarly suffixed tags even when naïve version sorting places them after the latest stable tag.

### Audit abandoned packages

- Search case-insensitively for variants such as `abandoned`, `archived`, and `unmaintained`; inspect every matching Makefile rather than relying on directory names.
- Distinguish a new release of the same project from a successor or incompatible fork. A successor may justify a report or a new package, but is not automatically a version bump of the old package.
- Check the authoritative repository's current HEAD date as well as release tags. If development resumed recently but no stable release exists, report the stable-release and git-snapshot choices separately.
- Verify package homepages independently of source URLs. Prefer the project's current HTTPS site or authoritative repository and replace dead, redirected, or transferred domains when the identity is clear.
- Remove an `abandoned` comment only when upstream activity proves it false and the user's requested policy permits the edit. Preserve comments that document real kernel, libc, compiler, or dependency constraints.

## Update the package

- Follow the package's historical versioning style: update `PKG_VERSION`, source revision/date, release, copyright, URL, and source hash only as applicable. In particular, preserve whether `PKG_VERSION` historically includes a leading `v`.
- For git sources, use the tagged commit rather than guessing a revision. Generate the archive through the OpenWrt download target, compute the resulting SHA-256, and replace any temporary `skip` hash with the exact value.
- Entware git-source archives may not be reproducible across separate generations. Use `PKG_MIRROR_HASH:=skip` only to create the archive once, immediately run `sha256sum dl/<exact-archive-name>`, and put that literal checksum into the Makefile. Keep and reuse that exact local archive for builds and later mirror publication; do not regenerate it after recording the checksum.
- Inspect upstream layout and build-system changes. Preserve Entware's `/opt` paths, public binary names, conffiles, init scripts, dependencies, and expected features unless the new upstream requires a deliberate migration.
- Treat a build-system migration as packaging work, not a mechanical version bump. When the newest line requires missing packages or downloads nested projects during compilation, identify the newest reproducible compatible release and document the newer-line constraint in the Makefile when appropriate.
- Remove obsolete patches when upstream has incorporated them. Adapt remaining patches to the new source rather than forcing failed hunks.
- Re-evaluate patch scope after large upstream layout changes. Keep changes that affect installed runtime behavior and Entware `/opt` paths; remove obsolete substitutions that only touched upstream integration tests or build fixtures unless those tests are actually part of the package build.
- If the package has or needs patches, run `make package/<name>/refresh` after the patches apply. Review the refreshed patch diff.
- If refresh is retrying a source version or a materially changed patch series, run the package-specific clean first so stale quilt state from the previous preparation cannot keep removed patches in `build_dir`.
- For upstreams with a custom Autoconf layout, prefer their checked-in `autogen.sh` with Entware host tools over generic `PKG_FIXUP:=autoreconf` when generic autoreconf discards or mislocates project macros and helper files.
- When an old compiler lacks a standard type or header assumed by current upstream, use the smallest compatibility patch and avoid changing generated build-tree files.
- When injecting version or build-date data with Go linker flags, inspect the upstream variable's expected representation. A variable parsed with `strconv.Atoi` needs a Unix timestamp, not a `YYYY-MM-DD` string. Run the built binary's version command to catch silent metadata errors such as a 1970 build date.

### Source acquisition

- Prefer release archives from the authoritative project. If no release archive exists but an authoritative signed/tagged git revision does, use `PKG_SOURCE_PROTO:=git`, pin the peeled tag commit, generate the OpenWrt archive with the download target, and replace `skip` with its exact mirror hash.
- If an authoritative server stalls on full downloads but supports HTTP ranges, it is acceptable to retrieve verified non-overlapping ranges into a temporary directory, assemble the exact archive, validate its byte count and compression format, and calculate the hash. Do not commit downloaded archives.
- A mirror may be used to transport the identical upstream archive, but do not substitute an unofficial source tree when upstream warns that third-party trees may differ.

For an OpenWrt host tool under `tools/`, the per-tool `download` target may be empty; use `make tools/download` to exercise the registered download rules and then hash the exact file in `dl`. Rebuild such a tool with its own targets, for example `make tools/<name>/clean`, `make tools/<name>/refresh`, and `make -j16 tools/<name>/compile`.

When updating `tools/go-src`, verify that the existing bootstrap compiler satisfies the new source tree's documented minimum instead of bumping `go-bootstrap` automatically. Inspect the new Go source when necessary: recent Go releases derive the required bootstrap branch algorithmically. If an Entware compatibility patch stops applying, check whether the new runtime now implements the same kernel fallback before adapting or deleting the patch. For patches affecting 32-bit runtime assembly, cross-compile the relevant standard-library target for `386`, `arm`, `mips`, and `mipsle` in addition to building the host compiler.

## Build and diagnose

Ensure the selected architecture's configuration and toolchain are actually complete. A staging directory alone is not proof. When needed, follow the Entware sequence:

```sh
make -j16 tools/install
make -j16 toolchain/install
make -j16 target/compile
```

Then build the affected package before any full build:

```sh
make -j16 package/<name>/compile
```

When a Makefile emits multiple packages or the selected `.config` does not enable every output under test, pass explicit `CONFIG_PACKAGE_<name>=y` values so compilation and packaging are not silently skipped.

On failure, use the exact failing target with one job and verbose output:

```sh
make -j1 package/<name>/compile V=s
```

Distinguish package regressions from missing/incomplete toolchain state. Do not run broad clean targets by default; if a changed source or patch set requires re-preparation, clean only the affected package when authorized by the repository instructions or user.

Use the target that matches what must be invalidated:

- `make package/<name>/clean` removes target-package state.
- `make package/<name>/host-clean` removes a package's host-build state when it has a separate host component.
- `make tools/<name>/clean` removes an OpenWrt tool build.

When the request requires every configured architecture, enumerate `configs/*.config`; for each file copy it to `.config`, run `make defconfig`, clean the affected package, and compile it with the repository's normal parallelism. Do this before committing. Confirm ARM packages produce every declared `hf`/`nohf` variant. An architecture excluded by an existing `DEPENDS:=@...` constraint is a documented skip, not a successful artifact build; report it explicitly.

## Verify and report

- Confirm the output package exists for the selected architecture.
- Inspect its archive contents, ELF interpreter, `/opt` layout, version strings, dependencies, and expected binaries/plugins/configuration.
- For runnable x64 packages, execute non-daemonizing version/help commands from the staged target root. Most pure-Go binaries are static; for a dynamically linked binary whose interpreter is under `/opt`, invoke the target loader from `staging_dir/toolchain-*` with its target library path rather than mistaking a host launch failure for a package failure.
- Match artifacts by both package name and new version so stale packages from earlier builds or sibling packages do not count as evidence for the update.
- Run `git diff --check` and explain unavoidable patch-format findings separately. Refreshed unified patches can legitimately contain a single-space blank context line; distinguish that from whitespace introduced into source changes.
- Report the verified update candidates and explicitly excluded/pinned packages, the build result and artifact path, relevant history patterns, and the complete `git diff -- <package-directory>`.
- Do not commit, push, publish source archives, or start a full repository build unless requested. If commits are requested, follow the feed history and keep one package per commit; never include unrelated or user-owned worktree changes.
