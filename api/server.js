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
  if (fs.existsSync("./data/state.json")) {
    return JSON.parse(fs.readFileSync("./data/state.json"));
  }
  return defaultState;
};

const saveState = (state) => {
  fs.writeFileSync("./data/state.json", JSON.stringify(state, null, 2));
};

const calculateState = (id, value) => {
  if (id == 1) {
    if (value > 15) return "empty";
    if (value > 5) return "half_full";
    return "full";
  }
  if (id == 2) {
    if (value == 0) return "normal";
    if (value == 1) return "tilted";
    return "fallen";
  }
  if (id == 3) {
    if (value > 800) return "closed";
    if (value > 400) return "half_open";
    return "open";
  }
};

app.get("/sensor", (req, res) => {
  const { id, value, key } = req.query;
  if (key !== "epitech2026") {
    return res.status(401).json({ error: "Invalid key" });
  }
  const state = loadState();
  state.trashcans[id] = {
    id: parseInt(id),
    value: parseFloat(value),
    state: calculateState(parseInt(id), parseFloat(value)),
  };
  saveState(state);
  res.json({ success: true, state: state.trashcans[id] });
});

app.get("/status", (req, res) => {
  const { id } = req.query;
  const state = loadState();
  res.json(state.trashcans[id]);
});

app.get("/status_all", (req, res) => {
  const state = loadState();
  res.json(Object.values(state.trashcans));
});

app.listen(3000, "0.0.0.0", () => {
  console.log("API rrunning on port 3000");
});
