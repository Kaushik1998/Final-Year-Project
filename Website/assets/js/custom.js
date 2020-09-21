//Ultrasonic Value update
const ultrasonicValue = document.getElementById("ultrasonicValue");
const getUltrasonicValue = () => {
  $.ajax({
    type: "GET",
    url: "https://kaushikiot.herokuapp.com/putObj",
    contentType: "application/json",
    success: function (response) {
      $(ultrasonicValue).html(response["Ultrasonic"]);
      $(ultrasonicValue).append(`<sub class="h6">cm</sub>`);
    },
  });
};

let ultrasonicInterval = setInterval(getUltrasonicValue, 500);

// Water Sensor
const waterSensorValue = document.getElementById("waterSensorValue");
const getWaterSensorValue = () => {
  $.ajax({
    type: "GET",
    url: "https://kaushikiot.herokuapp.com/putObj",
    contentType: "application/json",
    success: function (response) {
      $(waterSensorValue).html(response["WaterSensor"]);
    },
  });
};

let waterSensorInterval = setInterval(getWaterSensorValue, 500);

// LDR Sensor
const ldrValue = document.getElementById("ldrValue");
const getLightValue = () => {
  $.ajax({
    type: "GET",
    url: "https://kaushikiot.herokuapp.com/putObj",
    contentType: "application/json",
    success: function (response) {
      $(ldrValue).html(response["Light"]);
      $(ldrValue).append(`<sub class="h6">cd</sub>`);
    },
  });
};

let ldrInterval = setInterval(getLightValue, 500);

// LDR Sensor
const ldrLedValue = document.getElementById("ldrLedValue");
const getLDRLightValue = () => {
  $.ajax({
    type: "GET",
    url: "https://kaushikiot.herokuapp.com/putObj",
    contentType: "application/json",
    success: function (response) {
      let status = response["Light LED"];
      if (status) {
        $(ldrLedValue).html("ON");
      } else {
        $(ldrLedValue).html("OFF");
      }
    },
  });
};

let ldrLedInterval = setInterval(getLDRLightValue, 500);

// LED 13
let led13 = {
  LED: "OFF",
};
$("#led13").click(function (e) {
  e.preventDefault();
  $.ajax({
    type: "PUT",
    url: "https://kaushikiot.herokuapp.com/LED13",
    data: JSON.stringify(led13),
    contentType: "application/json",
    success: function (response) {
      if (response == "ON") {
        led13["LED"] = "OFF";
        $("#led13icon").addClass("ri-lightbulb-flash-line");
        $("#led13icon").removeClass("ri-lightbulb-line");
      } else if (response == "OFF") {
        led13["LED"] = "ON";
        $("#led13icon").removeClass("ri-lightbulb-flash-line");
        $("#led13icon").addClass("ri-lightbulb-line");
      }
    },
  });
});

// LED 9

let led9 = {
    LED: "OFF",
  };
  $("#led9").click(function (e) {
    e.preventDefault();
    $.ajax({
      type: "PUT",
      url: "https://kaushikiot.herokuapp.com/LED9",
      data: JSON.stringify(led9),
      contentType: "application/json",
      success: function (response) {
        if (response == "ON") {
          led9["LED"] = "OFF";
          $("#led9icon").addClass("ri-lightbulb-flash-line");
          $("#led9icon").removeClass("ri-lightbulb-line");
        } else if (response == "OFF") {
          led9["LED"] = "ON";
          $("#led9icon").removeClass("ri-lightbulb-flash-line");
          $("#led9icon").addClass("ri-lightbulb-line");
        }
      },
    });
  });