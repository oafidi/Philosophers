# Philosophers

## 🧠 Projet "Philosophers" - 42 School

Le projet **Philosophers** est un exercice emblématique de la programmation concurrente. Il nous plonge dans un problème algorithmique célèbre, afin de maîtriser la gestion fine des **threads**, la **synchronisation** avec les `mutex`, et la résolution de **problèmes critiques** comme le **deadlock** ou la **starvation**.

Ce projet est aussi une opportunité pour acquérir une rigueur essentielle dans l'industrie : **l'écriture de code robuste, efficace et sûr dans un environnement multithreadé**.

---

## 🔩 Ce que j'ai appris

Ce projet m’a permis de développer des compétences fondamentales pour le monde professionnel :

- **Modélisation de processus concurrents** à l’aide de threads POSIX (`pthread`).
- **Gestion des accès partagés** avec des `mutex` pour éviter les conditions de course.
- Mise en œuvre de **stratégies anti-deadlock** concrètes (ex : ordonnancement asymétrique des prises de fourchettes).
- **Surveillance en temps réel** des threads (thread de monitoring pour la détection de la mort d’un philosophe).
- Écriture de **code modulaire, maintenable et scalable**.
- Gestion du **temps précis** (milliseconde) pour simuler un environnement réaliste.
- **Communication sécurisée entre threads** (affichage synchronisé).

Ce projet m’a aussi permis d'adopter une approche rigoureuse et structurée face à des problématiques concrètes de **parallélisme**, un enjeu majeur pour toute entreprise travaillant avec des systèmes temps réel, des architectures multi-cœurs ou des serveurs haute performance.

---

## 🔧 Utilisation

### Compilation

```bash
make
```

### Exécution

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

- `number_of_philosophers`: Nombre de philosophes (et de fourchettes).
- `time_to_die`: Temps (en ms) avant qu’un philosophe ne meure s’il ne mange pas.
- `time_to_eat`: Temps (en ms) que met un philosophe à manger.
- `time_to_sleep`: Temps (en ms) que met un philosophe à dormir.
- `number_of_times_each_philosopher_must_eat` *(optionnel)* : Si tous les philosophes mangent ce nombre de fois, la simulation s’arrête.

### Exemple

```bash
./philo 5 800 200 200
```

---

## 🧵 Threads & Synchronisation

- Chaque philosophe est un thread.
- Les fourchettes sont représentées par des `mutex`.
- L’accès à la sortie est également protégé par un mutex (`print_mutex`) pour éviter les conflits d’affichage.

---

## 💥 Cas Gérés

- Un philosophe meurt si le `time_to_die` est dépassé.
- Prévention du deadlock : stratégies asymétriques mises en place.
- Détection correcte de la fin de simulation.
- Gestion du cas d’un seul philosophe.

---

## ✅ Règles

- Utilisation uniquement des `pthread` pour la gestion des threads.
- Précision du temps de simulation : milliseconde.

---

## 🧠 Pourquoi c'est important pour les entreprises

Ce projet est un **exercice réel de programmation système**. Les compétences acquises sont directement transférables vers :

- les applications multi-threadées haute performance,
- les systèmes embarqués,
- les jeux vidéo ou moteurs de rendu,
- les serveurs backend fortement concurrents,
- les simulateurs et systèmes critiques.

Il démontre ma **capacité à gérer la complexité technique**, à concevoir des architectures robustes, et à anticiper les défaillances.

---

## 📜 Licence

Ce projet est à but éducatif dans le cadre du cursus 42. Reproduction partielle ou complète interdite sans autorisation.

