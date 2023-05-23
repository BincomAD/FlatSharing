$(document).ready(function() {
  // Получаем URL текущей страницы
  var currentURL = window.location.href;

  // Ищем символ "?" в URL
  var queryStartIndex = currentURL.indexOf('?');
  if (queryStartIndex !== -1) {
    // Извлекаем часть URL, содержащую параметры
    var queryString = currentURL.substring(queryStartIndex + 1);

    // Разбиваем параметры на отдельные части
    var params = queryString.split('&');

    // Инициализируем переменные для offset и amount
    var offset, amount;

    // Проходимся по каждому параметру и ищем offset и amount
    params.forEach(function(param) {
      var parts = param.split('=');
      var paramName = decodeURIComponent(parts[0]);
      var paramValue = decodeURIComponent(parts[1]);

      if (paramName === 'offset') {
        offset = paramValue;
      } else if (paramName === 'amount') {
        amount = paramValue;
      }
    });

    // Проверяем, что offset и amount были найдены
    if (offset !== undefined && amount !== undefined) {
      // Формируем URL-адрес запроса с полученными параметрами
      var apiUrl = "http://127.0.0.1:8080/flats?offset=" + offset + "&amount=" + amount;
    } else {
      var apiUrl = "http://127.0.0.1:8080/flats?offset=10&amount=20";
    }
  } else {
    var apiUrl = "http://127.0.0.1:8080/flats?offset=10&amount=20";
  }

  // Отправляем AJAX запрос на сервер
  $.ajax({
    url: apiUrl,
    dataType: "json",
    success: function(data) {
      // Парсим полученные JSON данные
      var flats = data.param;

      // Отрисовываем каждую квартиру в HTML
      flats.forEach(function(flat) {
        var html = `
          <div class="col">
            <div class="card shadow-sm">
              <svg class="bd-placeholder-img card-img-top" width="100%" height="225" xmlns="http://www.w3.org/2000/svg"
                   role="img" aria-label="Placeholder: Thumbnail" preserveAspectRatio="xMidYMid slice" focusable="false">
                <title>Placeholder</title>
                <image href="static/img/apart3.jpg" width="100%" height="100%"/>
              </svg>
              <div class="card-body">
                <div class="d-flex justify-content-between align-items-center">
                  <div>
                    <h6>Цена:</h6>
                    <h6>Метраж:</h6>
                    <h6>Метро:</h6>
                  </div>
                  <div>
                    <h6>${flat.price}</h6>
                    <h6>${flat.square}</h6>
                    <h6>${flat.address}</h6>
                  </div>
                </div>
                <div class="d-flex justify-content-center mt-3">
                  <button type="button" class="btn btn-sm btn-primary">Арендовать</button>
                </div>
              </div>
            </div>
          </div>

        `;

        // Добавляем HTML для квартиры в контейнер
        $("#flats-container").append(html);
      });
    }
  });
});
