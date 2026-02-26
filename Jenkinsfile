pipeline {
    agent any

    stages {

        stage('Clone Repository') {
            steps {
                git 'https://github.com/Gamini-Sai-Lakshmi-Anjani/CC_LAB-6.git'
            }
        }

        stage('Build Backend Image') {
            steps {
                script {
                    docker.build("backend-image", "./backend")
                }
            }
        }

        stage('Run Backend Container') {
            steps {
                script {
                    docker.image("backend-image").run()
                }
            }
        }

        stage('Pull NGINX Image') {
            steps {
                sh 'docker pull nginx'
            }
        }

        stage('Run NGINX Container') {
            steps {
                sh '''
                docker run -d -p 9090:80 \
                -v ${WORKSPACE}/nginx/default.conf:/etc/nginx/conf.d/default.conf \
                nginx
                '''
            }
        }
    }
}
