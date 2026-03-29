const express = require("express");
const fs = require("fs");
const app = express();
app.use(express.json());

const defaultState = {
  trashcans: {
    1: { id: 1, state: "empty" },
    2: { id: 2, state: "normal" },
    3: { id: 3, state: "closed" },
  },
};

const loadState = () => {
  try {
    if (fs.existsSync("./data/state.json")) {
      return JSON.parse(fs.readFileSync("./data/state.json"));
    }
  } catch (err) {
    console.error("State file error resetting", err);
    saveState(defaultState);
  }
  return defaultState;
};

const saveState = (state) => {
  try {
    if (!fs.existsSync("./data")) {
      fs.mkdirSync("./data");
    }
    fs.writeFileSync("./data/state.json", JSON.stringify(state, null, 2));
  } catch (err) {
    console.error("Error saving state:", err);
  }
};

const calculateState = (id, value) => {
  try {
    if (id == 1) {
      if (value > 6) return "empty";
      if (value >= 3) return "half_full";
      return "full";
    }
    if (id == 2) {
      if (value == 0) return "normal";
      if (value == 1) return "tilted";
      return "fallen";
    }
    if (id == 3) {
      if (value < 90) return "closed";
      if (value < 700) return "half_open";
      return "open";
    }
  } catch (err) {
    console.error("Error calculating state:", err);
    return "unknown";
  }
};

app.get("/sensors", (req, res) => {
  try {
    const { id1, id2, id3, key } = req.query;
    if (key !== "epitech2026") {
      return res.status(401).json({ error: "Invalid key" });
    }
    if (!id1 || !id2 || !id3) {
      return res.status(400).json({ error: "Missing sensor values" });
    }
    const state = loadState();
    state.trashcans[1] = {
      id: 1,
      value: parseFloat(id1),
      state: calculateState(1, parseFloat(id1)),
    };
    state.trashcans[2] = {
      id: 2,
      value: parseFloat(id2),
      state: calculateState(2, parseFloat(id2)),
    };
    state.trashcans[3] = {
      id: 3,
      value: parseFloat(id3),
      state: calculateState(3, parseFloat(id3)),
    };
    saveState(state);
    res.json({ success: true, states: state.trashcans });
  } catch (err) {
    console.error("Error in /sensors:", err);
    res.status(500).json({ error: "Server error" });
  }
});

app.get("/sensor", (req, res) => {
  try {
    const { id, value, key } = req.query;
    if (key !== "epitech2026") {
      return res.status(401).json({ error: "Invalid key" });
    }
    if (!id || !value) {
      return res.status(400).json({ error: "Missing id or value" });
    }
    const state = loadState();
    state.trashcans[id] = {
      id: parseInt(id),
      value: parseFloat(value),
      state: calculateState(parseInt(id), parseFloat(value)),
    };
    saveState(state);
    res.json({ success: true, state: state.trashcans[id] });
  } catch (err) {
    console.error("Error in /sensor:", err);
    res.status(500).json({ error: "Server error" });
  }
});

app.get("/status", (req, res) => {
  try {
    const { id } = req.query;
    if (!id) {
      return res.status(400).json({ error: "Missing id" });
    }
    const state = loadState();
    if (!state.trashcans[id]) {
      return res.status(404).json({ error: "Trashcan not found" });
    }
    res.json(state.trashcans[id]);
  } catch (err) {
    console.error("Error in /status:", err);
    res.status(500).json({ error: "Server error" });
  }
});

app.get("/status_all", (req, res) => {
  try {
    const state = loadState();
    res.json(Object.values(state.trashcans));
  } catch (err) {
    console.error("Error in /status_all:", err);
    res.status(500).json({ error: "Server error" });
  }
});

process.on("uncaughtException", (err) => {
  console.error("Uncaught exception:", err);
});

process.on("unhandledRejection", (err) => {
  console.error("Unhandled rejection:", err);
});

app.listen(3000, "0.0.0.0", () => {
  console.log("API rrunning on port 3000");
});
