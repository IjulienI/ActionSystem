# ActionSystem

An Unreal Engine plugin that lets designers build gameplay sequences from small, reusable actions, set up directly in the Details panel of any actor.

![Status](https://img.shields.io/badge/status-in%20development-orange)
![Unreal Engine](https://img.shields.io/badge/Unreal%20Engine-5.4+-blue)
![License](https://img.shields.io/badge/license-MIT-green)

> **Work in progress.** The core is in place and usable, but the API is still moving. See the [roadmap](#roadmap).

---

## Why I built this

Working on team projects alongside game designers, I noticed that a system's power matters less than how quickly someone can pick it up. When a tool depends on documentation or a multi-step setup, it ends up underused, or used in ways it was never meant for.

ActionSystem is built around that idea, the tool should explain itself. Everything happens on the actor, in the Details panel, through a list of actions whose names say what they do. A designer can understand it at a glance, set up a sequence in seconds, and iterate on a prototype without waiting on a programmer.

## How it works

Add an **Action Component** to an actor and pick its root action: **Sequential**, **Parallel** or **Random**. Fill it with actions, nest other groups inside if needed, and call `ExecuteActions` from whatever should trigger it: an overlap, an interaction, a timer, another system.

```
Action Component
└── Sequential
    ├── Light Switch          (turn off the hallway lights)
    ├── Delay  2.0 s
    └── Parallel
        ├── Teleport Actor    (target: Instigator)
        └── Light Switch      (turn them back on)
```

Every action is an instanced UObject, created and configured inline in the Details panel. Nothing to place in the level, no asset to create.

### Lifecycle

| Step | Called | Purpose |
|---|---|---|
| `Init` | On `BeginPlay` | Cache references, apply the initial state |
| `Execute` | Each time the component is triggered | Do the work, receives the actor that triggered it |
| `Finish` | By the action, when its work is done | Tells the parent group it can move on |
| `Destroy` | On `EndPlay` | Clean up timers and state |

`Finish` is what makes time-based actions possible. A **Sequential** waits for each child to finish before starting the next one, a **Parallel** finishes once all of its children have, and a **Delay** simply finishes when its timer runs out.

### Targets

Actions that act on an actor use an `FActionTarget`, so designers choose who is affected without writing any logic:

| Source | Resolves to |
|---|---|
| `Self` | The actor that owns the Action Component |
| `Instigator` | The actor passed to `ExecuteActions`, for example the player who entered a trigger |
| `Reference` | A specific actor picked in the level |

## Available actions

| Action | Type | Description |
|---|---|---|
| **Sequential** | Group | Runs its actions one after another, each waiting for the previous one to finish |
| **Parallel** | Group | Runs all of its actions at once and finishes when they all have |
| **Random** | Group | Runs one of its actions, picked at random |
| **Delay** | Latent | Waits for a duration, in seconds |
| **Light Switch** | Instant | Toggles a list of lights, with a configurable starting state |
| **Teleport Actor** | Instant | Moves a target actor to a location |

## Writing a new action

The plugin provides two base classes, depending on whether the action takes time.

**Instant actions** do their work in one go. Inherit from `UInstantAction` and override `Run`. `Finish` is called for you.

```cpp
UCLASS()
class UHideActorAction : public UInstantAction
{
	GENERATED_BODY()

protected:
	virtual void Run_Implementation() override
	{
		if (AActor* Actor = ResolveTarget(Target))
		{
			Actor->SetActorHiddenInGame(true);
		}
	}

private:
	UPROPERTY(EditAnywhere, Category = "Action")
	FActionTarget Target;
};
```

**Latent actions** take time. Inherit from `UActionBase`, override `Execute`, and call `Finish()` once the work is done, as `UDelayAction` does with a timer.

New classes show up in the action picker straight away. Actions can also be created in Blueprint by subclassing `InstantAction` or `ActionBase`. A Blueprint latent action must call **Finish**, otherwise the group it belongs to will wait forever.

## Design decisions

- **Instanced UObjects rather than components or actors.** Actions only carry data and a bit of logic. As components they would clutter the actor's hierarchy, and as actors they would clutter the level. Instanced objects keep everything inside the Details panel of the actor that owns them.
- **A tree of groups instead of a flat list.** Flow control (sequence, parallel, random) is made of actions like any other. The component only holds one root group, and every new kind of flow can be added without touching it.
- **Completion through a delegate.** Actions report when they are done with `Finish`, so groups do not need to know what their children do or how long they take. Instant and latent actions plug into the same groups.
- **`InstantAction` seals `Execute`.** Its `Execute` is `final` and always calls `Finish` after `Run`, so a one-shot action can never forget to complete and stall its sequence.
- **`BlueprintNativeEvent` for the lifecycle.** The same action can be written in C++ or in Blueprint, and a Blueprint can extend a C++ action through `Super` calls.
- **World access through the Outer.** Actions override `GetWorld()` and resolve it from their owner, so world-dependent Blueprint nodes (spawning, timers, traces) work inside actions without extra setup.

## Current limitations

- Triggering a component again while its actions are still running is not handled yet. There is no "ignore", "restart" or "queue" policy.
- Running actions cannot be cancelled.

## Roadmap

**Core**
- [x] Instant and latent actions, with completion callbacks
- [x] Sequential, Parallel and Random groups
- [x] Instigator passed to `Execute`
- [x] Targets: self, instigator, specific actor
- [x] Re-trigger policy while running: ignore, restart or queue
- [x] Cancel running actions
- [ ] Targets by actor tag

**Flow control**
- [x] `Delay`
- [ ] `Branch`, `Do Once`, `Repeat`

**More actions**
- [x] Teleport an actor
- [x] Toggle lights
- [ ] Spawn actor, set visibility and collision, toggle component
- [ ] Move an actor over time, with a curve
- [ ] Trigger another actor's Action Component
- [ ] Play sound, Niagara effect, Level Sequence
- [ ] Load and unload streaming levels

**Tooling**
- [ ] Editor validation with clear messages (empty slots, missing targets)
- [ ] Custom names for actions, shown in the Details panel
- [ ] Debug logging and a console command to trigger actions by hand
- [ ] A demo level built entirely with ActionSystem

## Installation

1. Clone the repository into your project's `Plugins/` folder:
   ```
   cd YourProject/Plugins
   git clone https://github.com/IjulienI/ActionSystem.git
   ```
2. Regenerate project files and build.
3. Enable **ActionSystem** in *Edit → Plugins*.

Developed on Unreal Engine 5.4. Prebuilt releases for each engine version will be published on the [Releases](https://github.com/IjulienI/ActionSystem/releases) page.

## Feedback

If you try it out, I would love to hear how it went. Feel free to open an issue for a bug, a missing action, or an idea.

## About me

I'm Julien, a game programmer finishing my studies at ArtFX, focused on tools and gameplay programming in Unreal Engine. I'm currently looking for a position.

[GitHub](https://github.com/IjulienI) · [LinkedIn](https://www.linkedin.com/in/julien-soum-dev)

## License

MIT. See [`LICENSE`](LICENSE).