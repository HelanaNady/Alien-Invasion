![image](https://github.com/HelanaNady/Alien-Invasion/assets/137416623/eb4b450b-6a96-40be-90c9-2b30caa70ba2) </br>

<h1 align="center">👾 Simulate or Surrender 👾</h1>
<div align="center">

#### Whispers have become screams, eerie lights piercing the once-peaceful night sky,

**🛸 Alien invasion is no longer science fiction! 🛸**

</div>

The once-distant nightmare is now a present threat! The clock is ticking, humanity needed a glimpse into the future, a way to predict the enemy's moves before they unfold.

Faced with this impossible challenge, we developed **a simulated realm where strategies are tested, weaknesses exposed, and the enemy's playbook laid bare**. It is humanity's last chance to rewrite the future before the first shot shatters the silence!

## 📝 Introduction

"Alien Invasion" is a simulation game developed as part of a data structures course in our first year of computer engineering. The game involves Earth's army fighting against an alien army with randomly generated battle scenarios. The project's primary goal was to help us understand how to choose appropriate data structures for various tasks, design classes, and manage them effectively.

## 🕹️ Simulation Modes

Choose how to witness **humanity's last stand**:

- **Interactive Mode:** Watch the battle as it unfolds and let the aliens know you are watching!
- **Silent Mode:** Conduct a silent stealth mission and strategize in secret.

https://github.com/HelanaNady/Alien-Invasion/assets/137416623/e665c15d-3613-4e57-840f-621ae3b08516

## ⚔️ Battle Scenarios

The fate of Earth rests in your hands! Adapt your strategies and tactics as Earth's and alien forces vary in strength:

- **Balanced Power:** Engage in a battle where both Earth and alien armies are evenly matched, testing pure strategy.
- **Earth Overpower:** Lead a stronger Earth army against weaker or moderate alien forces for offensive strategies.
- **Alien Overpower:** Face overwhelming alien forces with a weaker Earth army to test defensive tactics.

## 🛠️ Getting Started

1. Clone the repo:
   ```sh
   git clone https://github.com/HelanaNady/Alien-Invasion.git
   ```
2. Open the project in Visual Studio Code or Visual Studio.
3. Build and run the project to start the simulation.

Adjust the battle scenarios through the prompt to test different strategies and the army's power.

## 🗂️ Data Structures Used

This project utilizes various data structures to efficiently manage the game's components:

| List Name      | Member of Class | Type           |
| -------------- | --------------- | -------------- |
| Earth Soldiers | EarthArmy       | Queue          |
| Earth Tanks    | EarthArmy       | Stack          |
| Earth Gunnery  | EarthArmy       | Priority Queue |
| Earth Healers  | EarthArmy       | Stack          |
| Alien Soldiers | AlienArmy       | Queue          |
| Alien Monsters | AlienArmy       | Array          |
| Alien Drones   | AlienArmy       | Deque          |

## 🧩 Class Design

The project follows an object-oriented design with the following main classes:

- `Army`: Represents an army, either Earth or alien, containing units.
- `Unit`: Represents a single unit within an army with attributes such as health and attack power.
- `Game`: Manages the battle, including the armies and their interactions and generates statistics at the end of the game.
- `RandomGenerator`: Generates random units every timestep based on specified probabilities.

### 📋 UML Diagram

![UML Diagram](https://lucid.app/publicSegments/view/2f21f577-3649-42d0-b463-5bd722aba50a/image.png)

## 🔒 License

This project is licensed under MIT License, See [License](LICENSE) for more information.

## 🌟 Collaborators

<table>
<tr>
  <td align = "center"> 
	<a href = "https://github.com/AhmedSobhy01">
	  <img src = "https://github.com/AhmedSobhy01.png" width = 100>
	  <br />
	  <sub> Ahmed Sobhy </sub>
	</a>
  </td>
  <td align = "center"> 
	<a href = "https://github.com/habibayman">
	  <img src = "https://github.com/habibayman.png" width = 100>
	  <br />
	  <sub> Habiba Ayman </sub>
	</a>
  </td>
  <td align = "center"> 
	<a href = "https://github.com/HelanaNady">
	  <img src = "https://github.com/HelanaNady.png" width = 100>
	  <br />
	  <sub> Helana Nady</sub>
	</a>
  </td>
</tr>
</table>
