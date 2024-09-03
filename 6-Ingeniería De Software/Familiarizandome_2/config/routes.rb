Rails.application.routes.draw do
  get 'index', to:’student#index'
  get '/student/:id', to:'student#show'
end