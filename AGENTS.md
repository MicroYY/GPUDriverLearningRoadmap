# Agent Instructions

## Project Overview

This repository is a GPU driver learning roadmap organized as course-style
documentation:

- `docs/` contains the preface, long-term roadmap, source-reading checklist,
  and weekly retrospective template.
- `sessions/` contains numbered learning sessions.
- `labs/` contains numbered labs that correspond to the sessions.
- `sources/` contains upstream source code managed as Git submodules
  (`linux`, `mesa`, `libdrm`, and `igt-gpu-tools`).

The main repository is documentation-first. Treat `sources/` as reference
material unless the user explicitly asks to inspect or modify submodule
contents.

## Working Guidelines

- Preserve the existing Chinese documentation style in `README.md`, `docs/`,
  `sessions/`, and `labs/`.
- Keep session and lab numbering aligned. If adding or renaming a session or
  lab, update the matching index files and roadmap links.
- Prefer small, reviewable Markdown edits. Do not reformat unrelated sections.
- Use relative Markdown links for files inside the repository.
- Be careful with `sources/`: it is large and externally maintained. Avoid
  broad searches there unless source inspection is required; prefer scoped
  paths such as `sources/linux/drivers/gpu/drm` when searching.
- Do not commit generated build outputs, editor files, or local environment
  directories. Follow `.gitignore`.

## Session and Lab Writing Standard

- Treat `sessions/` as lecture notes only.
- Session files should focus on explanation, concepts, boundaries, call paths,
  and source-reading guidance. Prefer more substantive teaching content over
  task-management prose.
- Session files should link to the corresponding lab, but should not include
  execution-oriented sections such as deliverables, checklists, completion
  criteria, or duplicated lab steps.
- Treat `labs/` as hands-on execution pages only.
- Lab files should be organized into two sections:
  - `代码练习`
  - `概念解释`
- In labs, make `代码练习` the main body.
- The `概念解释` section should ask the reader to explain concepts based on
  the commands, code, or source paths they just used. Do not re-teach the same
  knowledge points from the session inside the lab.
- Prefer concrete commands, code, file paths, and executable steps in labs
  instead of generic advice.
- Avoid repeating the same structure across session and lab. In particular, do
  not duplicate deliverables, checklists, completion standards, or broad
  learning summaries in both places.

## Useful Commands

There is no package manager or project test suite configured for this repo.
For documentation changes, use focused checks:

```bash
git status --short
rg -n "term-or-link" README.md docs sessions labs
```

Submodules are initialized with:

```bash
git submodule update --init --depth 1 --filter=blob:none
```

For a smaller user-space source checkout:

```bash
git submodule update --init --depth 1 --filter=blob:none sources/mesa sources/libdrm sources/igt-gpu-tools
```

Windows native filesystems may warn about case conflicts in a full Linux kernel
checkout. Prefer WSL/Linux filesystems for `sources/linux`, or use the sparse
checkout described in `README.md`.

## AGENTS.md Maintenance

After any non-trivial project change, check whether this file should be
updated.

Update `AGENTS.md` when a change affects:

- project structure or important directories
- install, development, test, build, sync, or deploy commands
- required environment variables, secrets, credentials, or proxy expectations
- external integrations or API workflows
- generated files or files agents should not edit
- coding conventions, architectural patterns, or testing expectations
- recurring pitfalls discovered while working on the project

Do not update `AGENTS.md` for small bug fixes, one-off implementation details,
or information already obvious from nearby code, package scripts, or existing
docs.
