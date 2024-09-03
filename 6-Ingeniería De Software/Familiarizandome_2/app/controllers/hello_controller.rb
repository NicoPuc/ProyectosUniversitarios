class HelloController < ApplicationController
    def sayhi
        render json:'Hello World!!'
        end
end
