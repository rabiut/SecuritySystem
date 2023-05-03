async function fetchData() {
  try {
    const response = await fetch("/motion-data");
    const data = await response.json();

    const container = document.getElementById("motion-data");
    container.innerHTML = ""; // Clear the existing content

    if (data.length === 0) {
      const messageElement = document.createElement("p");
      messageElement.textContent = "No data to display";
      container.appendChild(messageElement);
      return;
    }

    displayMostRecentImage(data, container);
    // Uncomment the line below if you want to display all images
    // displayAllImages(data, container);
  } catch (error) {
    console.error("Error fetching data:", error);
  }
}

function displayMostRecentImage(data, container) {
  const mostRecentItem = data[data.length - 1];
  const imageElement = document.createElement("img");
  imageElement.src = mostRecentItem.image_data;
  imageElement.alt = "alt text";

  const infoTextElement = document.createElement("p");
  infoTextElement.textContent = mostRecentItem.info_text;

  container.appendChild(imageElement);
  container.appendChild(infoTextElement);
}

function displayAllImages(data, container) {
  data.reverse().forEach((item) => {
    const imageElement = document.createElement("img");
    imageElement.src = item.image_data;
    imageElement.alt = "alt text";

    const infoTextElement = document.createElement("p");
    infoTextElement.textContent = item.info_text;

    container.appendChild(imageElement);
    container.appendChild(infoTextElement);
  });
}

function startPolling(interval) {
  fetchData(); // Fetch data immediately
  setInterval(fetchData, interval); // Fetch data periodically
}

const pollInterval = 5000; // 5 seconds
startPolling(pollInterval);
