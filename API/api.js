const express = require("express");
const multer = require("multer");
const fs = require("fs");
const path = require("path");
const sqlite = require("sqlite");
const sqlite3 = require("sqlite3");

const app = express();
const upload = multer({ dest: "images/" });

// route in to get the image data from the database
app.get("/motion-data", async (req, res) => {
  try {
    const db = await sqlite.open({
      filename: "security_system.db",
      driver: sqlite3.Database,
    });

    // Create the table if it doesn't exist
    await createTableIfNotExists(db);

    const data = await db.all("SELECT * FROM motion_data");
    await db.close();

    const base64Data = data
      .filter((item) => item.image_data)
      .map((item) => ({
        ...item,
        image_data: `data:image/jpeg;base64,${item.image_data.toString(
          "base64"
        )}`,
      }));

    res.status(200).json(base64Data);
  } catch (error) {
    console.error("Error fetching data from database:", error);
    res.status(500).json({ message: "Error fetching data from database" });
  }
});

app.post("/motion-sensor", upload.single("image"), async (req, res) => {
  const imageFile = req.file;
  const infoText = req.body.info_text;

  // Process the image and info_text
  await processImageAndInfo(imageFile, infoText);

  // Return the response
  res.status(201).json({ message: "Data received" });
});

async function createTableIfNotExists(db) {
  const createTableQuery = `CREATE TABLE IF NOT EXISTS motion_data (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    image_data BLOB NOT NULL,
    info_text TEXT NOT NULL,
    timestamp DATETIME NOT NULL
  )`;

  await db.run(createTableQuery);
}

async function processImageAndInfo(imageFile, infoText) {
  const timestamp = new Date().toISOString();
  const infoTextWithTimestamp = `${infoText} - Timestamp: ${timestamp}`;

  // Save the image and infoTextWithTimestamp to the database
  try {
    await saveToDatabase(imageFile, infoTextWithTimestamp);
  } catch (error) {
    console.error("Error saving to database:", error);
  }

  // Log the received data
  console.log(
    `Received image: ${imageFile.filename}, Info text: ${infoTextWithTimestamp}`
  );
}

async function saveToDatabase(imageFile, infoText) {
  // Add the appropriate file extension based on the mimetype
  let fileExtension;
  if (imageFile.mimetype === "image/jpeg") {
    fileExtension = ".jpg";
  } else if (imageFile.mimetype === "image/png") {
    fileExtension = ".png";
  } else {
    console.error("Unsupported image format");
    return;
  }

  // Rename the file with the extension
  const newFilename = imageFile.filename + fileExtension;
  const newPath = path.join(imageFile.destination, newFilename);
  fs.renameSync(imageFile.path, newPath);

  // Read the image file data
  const imageData = fs.readFileSync(newPath);

  // Save the image and infoText to the database
  const db = await sqlite.open({
    filename: "security_system.db",
    driver: sqlite3.Database,
  });
  // Create the table if it doesn't exist
  await createTableIfNotExists(db);

  // Delete all existing images from the database
  //   try {
  //     await deleteAllRows(db);
  //   } catch (error) {
  //     console.error("Error deleting existing rows:", error);
  //   }

  const insertQueryData =
    "INSERT INTO motion_data (image_data, info_text, timestamp) VALUES (?, ?, ?)";
  const timestamp = new Date().toISOString();
  await db.run(insertQueryData, [imageData, infoText, timestamp]);
  await db.close();
}

async function deleteAllRows(db) {
  const deleteQuery = "DELETE FROM motion_data";
  await db.run(deleteQuery);
  await db.run("DELETE FROM sqlite_sequence WHERE name='motion_data'");
}

// Serve static files from the "public" folder
app.use(express.static("public"));

// Serve images from the "images" folder
app.use("/images", express.static("images"));

const port = 5000;
app.listen(port, () => {
  console.log(`API server running on port ${port}`);
});
