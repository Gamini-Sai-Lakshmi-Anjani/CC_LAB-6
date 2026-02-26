pipeline {
    agent any

    stages {

        stage('Create Network') {
            steps {
                sh '''
                docker network rm labnet || true
                docker network create labnet
                '''
            }
        }

        stage('Build Backend Image') {
            steps {
                sh 'docker build -t backend-app backend'
            }
        }

        stage('Deploy Backend Containers') {
            steps {
                sh '''
                docker rm -f backend1 backend2 || true
                docker run -d --name backend1 --network labnet backend-app
                docker run -d --name backend2 --network labnet backend-app
                sleep 3
                '''
            }
        }

        stage('Start NGINX Load Balancer') {
            steps {
                sh '''
                docker rm -f nginx-lb || true
                docker run -d --name nginx-lb -p 80:80 --network labnet nginx
                sleep 2
                docker cp nginx/default.conf nginx-lb:/etc/nginx/conf.d/default.conf
                docker exec nginx-lb nginx -s reload
                '''
            }
        }
    }
}
