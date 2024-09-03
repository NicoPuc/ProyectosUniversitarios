Rails.application.routes.draw do
  # Define your application routes per the DSL in https://guides.rubyonrails.org/routing.html
  resources :reviews

  resources :requests do 
    member do
      put :accept
      put :reject
    end
  end

  resources :chats do
    resources :messages
  end
  resources :chats
  post 'start_chat', to: 'chats#start', as: 'start_chat'


  #requests
  #get 'requests/new', to: 'requests#new', as: 'new_request' 
  #get 'requests', to: 'requests#index', as: 'requests'
  #get '/requests/:id', to: 'requests#show', as: :request
  #get '/requests/:id/edit', to: 'requests#edit', as: :edit_request
  #get '/requests/:id/edit', to: 'requests#edit', as: :edit_request
  #patch '/requests/:id', to: 'requests#update'
  #delete '/requests/:id', to: 'requests#destroy'


  #actividads
  #get '/actividads/new', to: 'actividads#new', as: :new_actividad
  #get '/actividads', to: 'actividads#index'
  #get '/actividads/:id', to: 'actividads#show', as: :actividad
  #post '/actividads', to:  'actividads#create'
  #get '/actividads/:id/edit', to: 'actividads#edit', as: :edit_actividad
  #patch '/actividads/:id', to: 'actividads#update'
  #delete '/actividads/:id', to: 'actividads#destroy'
  #
  resources :actividads
  get 'render/index'
  get "up" => "rails/health#show", as: :rails_health_check
  # Defines the root path route ("/")
  # root "articles#index"
  # Rutas no necesariamente creadas para User pero si utilizadas:
  devise_for :users
  root to: "render#index"

  devise_scope :user do
    get 'users/sign_out' => "devise/sessions#destroy"
  end
  

end
