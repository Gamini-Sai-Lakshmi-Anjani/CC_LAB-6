pipeline {
    agent any

    stages {

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
        sh 'docker run -d -p 9090:80 nginx'
    }

        }
    }
}
