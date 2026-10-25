# ActionSystem

A small Unreal Engine plugin that lets designers attach reusable, configurable actions to any actor and trigger them from a single call.

![Status](https://img.shields.io/badge/status-in%20development-orange)
![Unreal Engine](https://img.shields.io/badge/Unreal%20Engine-5.4+-blue)
![License](https://img.shields.io/badge/license-MIT-green)

> **Work in progress.** The core works and is usable, but the API is still moving and several features are missing. See the [roadmap](#roadmap).

---

## Why I built this

Working on team projects alongside game designers, I noticed that a system's power matters less than how quickly someone can pick it up. When a tool depends on documentation or a multi-step setup, it ends up underused, or used in ways it was never meant for.

ActionSystem is built around that idea, the tool should explain itself. Everything happens on the actor, in the Details panel, through a list of actions whose names say what they do. A designer can understand it at a glance, set up a sequence in seconds, and iterate on a prototype without waiting on a programmer.

## How it works

The system has two pieces.

**`UActionBase`** is a small, self-contained unit of behavior with its own properties: *destroy these actors*, *toggle these lights*. Actions are instanced UObjects (`EditInlineNew`, `DefaultToInstanced`), so each one is created and configured inline, in the Details panel of the actor that owns it.

**`UActionComponent`** holds an ordered list of actions. You add it to an actor, pick actions from the dropdown, fill in their settings, and call `ExecuteActions()` from wherever makes sense: an overlap, an interaction, a timer, another system.

Each action goes through a simple lifecycle:

| Step | Called | Typical use |
|---|---|---|
| `Init` | On `BeginPlay`, or manually | Cache references, apply the initial state |
| `Execute` | Each time the component is triggered | Do the work |
| `Destroy` | On `EndPlay`, or manually | Clean up |

### Writing a new action

In C++, inherit from `UActionBase` and override what you need:

```cpp
UCLASS(BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class UMyAction : public UActionBase
{
	GENERATED_BODY()

public:
	virtual void Execute_Implementation() override;

private:
	UPROPERTY(EditAnywhere, Category = "Action")
	TArray<TObjectPtr<AActor>> Targets;
};
```

The class shows up in the component's action picker straight away. Designers can also create actions in Blueprint by subclassing `ActionBase` and implementing the `Init`, `Execute` and `Destroy` events.

### Available actions

- **Destroy Actors**: destroys a list of actors.
- **Light Switch**: toggles a list of lights, with a configurable starting state.

## Design decisions

A few choices I made along the way, and why:

- **Instanced UObjects rather than components or actors.** Actions only carry data and a bit of logic. Making them components would clutter the actor's hierarchy. Making them actors would clutter the level. Instanced objects keep everything inside the Details panel of the actor that owns them.
- **`BlueprintNativeEvent` for the lifecycle.** The same action can be written in C++ for performance or in Blueprint for fast iteration, and a Blueprint can extend a C++ action through `Super` calls.
- **World access through the Outer.** Actions override `GetWorld()` and resolve it from their owning component, so world-dependent nodes (spawning, timers, traces) work inside Blueprint actions without any extra setup.
- **Opt-out initialization.** Actions initialize on `BeginPlay` by default. An action can disable *Auto Init* and be initialized later, which is useful when it depends on something that does not exist yet at startup.

## Current limitations

Being upfront about what does not work yet:

- `Execute` is synchronous. Actions that take time (a delay, a movement, a sequence) cannot signal when they are done yet. This is the next big piece of work.
- Targets are hard references to actors placed in the level. That works for level instances, but not for actions set up on a Blueprint class.
- `DestroyActions()` clears the action list, so a component cannot be re-initialized after it has been destroyed.

## Roadmap

**Next up**
- [ ] Latent actions: completion callback, sequential and parallel execution, cancellation
- [ ] Instigator passed to `Execute`, so actions can target whoever triggered them
- [ ] Flexible targets: self, instigator, specific actor, or actors with a tag

**Flow control**
- [ ] `Delay`, `Sequence`, `Parallel`, `Branch`, `Do Once`, `Random`

**More actions**
- [ ] Spawn actor, set visibility and collision, toggle component
- [ ] Move or teleport an actor
- [ ] Trigger another actor's Action Component
- [ ] Play sound, Niagara effect, Level Sequence
- [ ] Load and unload streaming levels

**Tooling**
- [ ] Editor validation (missing targets, empty entries)
- [ ] Debug logging and a console command to trigger actions by hand
- [ ] A demo level built entirely with ActionSystem

## Installation

**From a release**

1. Download the zip matching your engine version from the [Releases](https://github.com/IjulienI/ActionSystem/releases) page.
2. Extract it into your project's `Plugins/` folder.
3. Enable **ActionSystem** in *Edit → Plugins* and restart the editor.

**From source** (C++ projects)

```
cd YourProject/Plugins
git clone https://github.com/IjulienI/ActionSystem.git
```

Then regenerate project files and build.

Developed on Unreal Engine 5.4. Release builds are provided for 5.4 and later.

## Feedback

If you try it out, I would love to hear how it went. Feel free to open an issue for a bug, a missing action, or an idea.

## About me

I'm Julien, a game programmer finishing my studies, with a focus on gameplay and tools programming in Unreal Engine. I'm currently looking for a position.

- [LinkedIn](www.linkedin.com/in/julien-soum-dev)

## License

MIT. See [`LICENSE`](LICENSE).