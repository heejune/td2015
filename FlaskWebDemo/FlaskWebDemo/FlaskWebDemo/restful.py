# -*- coding: utf-8 -*-

from FlaskWebDemo import app
from flask import jsonify, make_response, request, url_for, request

# http://blog.miguelgrinberg.com/post/designing-a-restful-api-with-python-and-flask

tasks = [
    {
        'id': 1,
        'title': u'Buy groceries',
        'description': u'Milk, Cheese, Pizza, Fruit, Tylenol', 
        'image': '/static/images/pizza.jpg',
        'done': False
    },
    {
        'id': 2,
        'title': u'Learn Python',
        'description': u'Need to find a good Python tutorial on the web', 
        'image': '/static/images/python_logo.jpg',
        'done': False
    },
    {
        'id': 3,
        'title': u'VS2015 설치하기',
        'description': u'IntelliTrace 기능은 Enterprise SKU 이상에서만 지원', 
        'image': '/static/images/visual-studio-logo.png',
        'done': True
    },
    {
        'id': 4,
        'title': u'Write new blog post',
        'description': u'Uploading a new blog post to heejune.me', 
        'image': '/static/images/heejune.png',
        'done': False
    },
    {
        'id': 5,
        'title': u'C++ 발표하기',
        'description': u'C++11 topic 발표하기', 
        'image': '/static/images/cpp_lecture.png',
        'done': False
    },
    {
        'id': 6,
        'title': u'Submit cousera h/w',
        'description': u'Finishing assignments', 
        'image': '/static/images/cousera.png',
        'done': False
    },
    {
        'id': 7,
        'title': u'Backup photos',
        'description': u'Buy NAS and backup family photos', 
        'image': '/static/images/NAS.png',
        'done': False
    },
    {
        'id': 8,
        'title': u'Family Trip',
        'description': u'Preparing family trip to Jeju', 
        'image': '/static/images/travel.png',
        'done': False
    },
    {
        'id': 9,
        'title': u'Bug fixes',
        'description': u'Finding bugs ad fix them', 
        'image': '/static/images/bugs.png',
        'done': False
    },
    {
        'id': 10,
        'title': u'Finish books',
        'description': u'Finish books queued in the list', 
        'image': '/static/images/book.png',
        'done': False
    }]

@app.errorhandler(404)
def not_found(error):
    return make_response(jsonify({'error': 'Not found'}), 404)

def make_public_task(task):
    new_task = {}
    for field in task:
        if field == 'id':
            new_task['uri'] = url_for('get_task', task_id=task['id'], _external=True)
        new_task[field] = task[field]   # include 'id' to return json
        #else:
        #    new_task[field] = task[field]
    return new_task

@app.route('/todo/api/v1.0/tasks', methods=['GET'])
def get_tasks():
    return jsonify({'tasks': [make_public_task(task) for task in tasks]})

@app.route('/todo/api/v1.0/tasks/<int:task_id>', methods=['GET'])
def get_task(task_id):
    task = [task for task in tasks if task['id'] == task_id]
    if len(task) == 0:
        abort(404)
    return jsonify({'task': task[0]})

@app.route('/todo/api/v1.0/tasks', methods=['POST'])
def create_task():
    if not request.json or not 'title' in request.json:
        abort(400)
    task = {
        'id': tasks[-1]['id'] + 1,
        'title': request.json['title'],
        'description': request.json.get('description', ""),
        'image': request.json.get('image', ""),
        'done': False
    }
    tasks.append(task)
    return jsonify({'task': task}), 201

@app.route('/todo/api/v1.0/tasks/<int:task_id>', methods=['PUT'])
def update_task(task_id):
    task = [task for task in tasks if task['id'] == task_id]
    if len(task) == 0:
        abort(404)
    if not request.json:
        abort(400)
    if 'title' in request.json and type(request.json['title']) != str:
        abort(400)
    if 'description' in request.json and type(request.json['description']) is not str:
        abort(400)
    if 'image' in request.json and type(request.json['image']) is not str:
        abort(400)
    if 'done' in request.json and type(request.json['done']) is not bool:
        abort(400)
    task[0]['title'] = request.json.get('title', task[0]['title'])
    task[0]['description'] = request.json.get('description', task[0]['description'])
    task[0]['image'] = request.json.get('image', task[0]['image'])
    task[0]['done'] = request.json.get('done', task[0]['done'])
    return jsonify({'task': task[0]})

@app.route('/todo/api/v1.0/tasks/<int:task_id>', methods=['DELETE'])
def delete_task(task_id):
    task = [task for task in tasks if task['id'] == task_id]
    if len(task) == 0:
        abort(404)
    tasks.remove(task[0])
    return jsonify({'result': True})
