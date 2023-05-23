const express = require('express');
const axios = require('axios');
const { JSDOM } = require('jsdom');
const fs = require('fs');

const app = express();
app.use(express.static('static'));
const port = 8081;

app.get('/', (req, res) => {
  const offset = req.query.offset || 1000;
  const amount = req.query.amount || 10;
  const apiUrl = `http://127.0.0.1:8080/flats?offset=${offset}&amount=${amount}`;

  axios.get(apiUrl)
    .then(response => {
      const data = response.data;
      const flats = data.param;

      // Читаем содержимое файла index.html
      fs.readFile('index.html', 'utf8', (err, fileData) => {
        if (err) {
          console.error(err);
          res.status(500).send('Internal Server Error');
          return;
        }

        // Создаем виртуальное DOM-дерево с помощью JSDOM
        const dom = new JSDOM(fileData);
        const document = dom.window.document;

        // Находим место в файле, куда нужно вставить квартиры
        const flatsContainer = document.getElementById('flats-container');

        // Создаем элементы списка квартир и добавляем их в виртуальный DOM
        flats.forEach(flat => {
          const div = document.createElement('div');
          div.innerHTML = `
          <div class="col">
          <div class="card shadow-sm">
            <svg class="bd-placeholder-img card-img-top" width="100%" height="225" xmlns="http://www.w3.org/2000/svg"
                 role="img" aria-label="Placeholder: Thumbnail" preserveAspectRatio="xMidYMid slice" focusable="false">
              <title>Placeholder</title>
              <image href="/img/apart1.jpg" width="100%" height="100%"/>
            </svg>
            <div class="card-body">
              <div class="d-flex justify-content-between align-items-center">
                <div>
                  <h6>Цена:</h6>
                  <h6>Метраж:</h6>
                  <h6>Метро:</h6>
                </div>
                <div>
                  <h6> ${flat.price}</h6>
                  <h6> ${flat.square}</h6>
                  <h6> ${flat.address}</h6>
                </div>
              </div>
              <div class="d-flex justify-content-center mt-3">
                <button type="button" class="btn btn-sm btn-primary"><a href="/flat?id=${flat.idFlat}">Арендовать</a></button>
              </div>
            </div>
          </div>
        </div>
          `;
          flatsContainer.appendChild(div);
        });

        // Получаем HTML-код из виртуального DOM
        const html = document.documentElement.outerHTML;

        // Отправляем HTML-страницу как ответ на запрос
        res.send(html);
      });
    })
    .catch(error => {
      console.error(error);
      res.status(500).send('Internal Server Error');
    });
});

app.get('/catalog', (req, res) => {
  const offset = req.query.offset || 1000;
  const amount = req.query.amount || 10;
  const apiUrl = `http://127.0.0.1:8080/flats?offset=${offset}&amount=${amount}`;

  axios.get(apiUrl)
    .then(response => {
      const data = response.data;
      const flats = data.param;

      // Читаем содержимое файла index.html
      fs.readFile('templates/catalog.html', 'utf8', (err, fileData) => {
        if (err) {
          console.error(err);
          res.status(500).send('Internal Server Error');
          return;
        }

        // Создаем виртуальное DOM-дерево с помощью JSDOM
        const dom = new JSDOM(fileData);
        const document = dom.window.document;

        // Находим место в файле, куда нужно вставить квартиры
        const flatsContainer = document.getElementById('flats-container');

        // Создаем элементы списка квартир и добавляем их в виртуальный DOM
        flats.forEach(flat => {
          const div = document.createElement('div');
          div.innerHTML = `
          <div class="col">
          <div class="card shadow-sm">
            <svg class="bd-placeholder-img card-img-top" width="100%" height="225" xmlns="http://www.w3.org/2000/svg"
                 role="img" aria-label="Placeholder: Thumbnail" preserveAspectRatio="xMidYMid slice" focusable="false">
              <title>Placeholder</title>
              <image href="/img/apart1.jpg" width="100%" height="100%"/>
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
                <a href="/flat?id=${flat.idFlat}" class="btn btn-sm btn-primary">Арендовать</a>
              </div>
              <span class="badge bg-danger position-absolute top-0 start-0">Занято</span>
            </div>
          </div>
        </div>
          `;
          flatsContainer.appendChild(div);
        });

        // Получаем HTML-код из виртуального DOM
        const html = document.documentElement.outerHTML;

        // Отправляем HTML-страницу как ответ на запрос
        res.send(html);
      });
    })
    .catch(error => {
      console.error(error);
      res.status(500).send('Internal Server Error');
    });
});

app.get('/flat', (req, res) => {
  const id = req.query.id ;
  const apiUrl = `http://127.0.0.1:8080/flat?id=${id}`;

  axios.get(apiUrl)
    .then(response => {
      const data = response.data;
      const flat = data.param;

      // Читаем содержимое файла index.html
      fs.readFile('templates/flat.html', 'utf8', (err, fileData) => {
        if (err) {
          console.error(err);
          res.status(500).send('Internal Server Error');
          return;
        }

        const dom = new JSDOM(fileData);
        const document = dom.window.document;

        const flatsContainer = document.getElementById('container-flat');

        // Создаем элементы списка квартир и добавляем их в виртуальный DOM
          
        const div = document.createElement('div');
        div.innerHTML = `
          <div class="row">
            <div class="col-md-6">
              <div class="apartment-description">
                <h3>Квартира в прекрасном районе</h3>
                <p><strong>Владелец:</strong> ${data.idUserOwner}</p>
                <p><strong>Стоимость:</strong> ${data.price}</p>
                <p><strong>Расположение:</strong> ${data.address}</p>
                <p><strong>Описание:</strong> ${data.descrition}</p>
                <p><strong>Метраж:</strong> ${data.square}.</p>
              </div>
            </div>
            <div class="col-md-6">
              <div class="calendar">
                <label for="arrival-date">Дата въезда:</label>
                <input type="text" id="arrival-date" readonly>
                <label for="departure-date">Дата выезда:</label>
                <input type="text" id="departure-date" readonly>
                <div id="price"></div>
                <a href="/rent" class="btn btn-sm btn-primary">Арендовать</a>
              </div>
            </div>
          </div>
          `;
        flatsContainer.appendChild(div);


        // Получаем HTML-код из виртуального DOM
        const html = document.documentElement.outerHTML;

        // Отправляем HTML-страницу как ответ на запрос
        res.send(html);
      });
    })
    .catch(error => {
      console.error(error);
      res.status(500).send('Internal Server Error');
    });
});

app.get('/auth', (req, res) => {
  const offset = req.query.offset || 1000;
  const amount = req.query.amount || 10;
  const apiUrl = `http://127.0.0.1:8080/flats?offset=${offset}&amount=${amount}`;

  axios.get(apiUrl)
    .then(response => {
      const data = response.data;
      const flats = data.param;

      // Читаем содержимое файла index.html
      fs.readFile('templates/auth.html', 'utf8', (err, fileData) => {
        if (err) {
          console.error(err);
          res.status(500).send('Internal Server Error');
          return;
        }

        // Создаем виртуальное DOM-дерево с помощью JSDOM
        const dom = new JSDOM(fileData);
        const document = dom.window.document;

        // Получаем HTML-код из виртуального DOM
        const html = document.documentElement.outerHTML;

        // Отправляем HTML-страницу как ответ на запрос
        res.send(html);
      });
    })
    .catch(error => {
      console.error(error);
      res.status(500).send('Internal Server Error');
    });
});

app.get('/faq', (req, res) => {
  const apiUrl = `http://127.0.0.1:8080/`;

  axios.get(apiUrl)
    .then(response => {
      const data = response.data;
      const flats = data.param;

      // Читаем содержимое файла index.html
      fs.readFile('templates/faq.html', 'utf8', (err, fileData) => {
        if (err) {
          console.error(err);
          res.status(500).send('Internal Server Error');
          return;
        }

        // Создаем виртуальное DOM-дерево с помощью JSDOM
        const dom = new JSDOM(fileData);
        const document = dom.window.document;

        // Получаем HTML-код из виртуального DOM
        const html = document.documentElement.outerHTML;

        // Отправляем HTML-страницу как ответ на запрос
        res.send(html);
      });
    })
    .catch(error => {
      console.error(error);
      res.status(500).send('Internal Server Error');
    });
});

app.get('/registration', (req, res) => {
  const apiUrl = `http://127.0.0.1:8080/`;

  axios.get(apiUrl)
    .then(response => {
      const data = response.data;
      const flats = data.param;

      // Читаем содержимое файла index.html
      fs.readFile('templates/registration.html', 'utf8', (err, fileData) => {
        if (err) {
          console.error(err);
          res.status(500).send('Internal Server Error');
          return;
        }

        // Создаем виртуальное DOM-дерево с помощью JSDOM
        const dom = new JSDOM(fileData);
        const document = dom.window.document;

        // Получаем HTML-код из виртуального DOM
        const html = document.documentElement.outerHTML;

        // Отправляем HTML-страницу как ответ на запрос
        res.send(html);
      });
    })
    .catch(error => {
      console.error(error);
      res.status(500).send('Internal Server Error');
    });
});

const urlencodedParser = express.urlencoded({extended: false});

app.post("/registration", urlencodedParser, function (request, response) {
  const apiUrl = `http://127.0.0.1:8080/registration`;

  axios.post(apiUrl, {
    login: request.body.login,
    password: request.body.password,
    name: request.body.name,
    email: request.body.email,
    phoneNuber: request.body.phone 
  })
  .then(function (response) {
    console.log(response);
  })
  .catch(function (error) {
    console.log(error);
  });
});

app.listen(port, () => {
  console.log(`Server is listening on port ${port}`);
});